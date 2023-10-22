// asagao/source/interface.cpp


#include "stdafx.h"

#include "asagao.hpp"

#include "game_object.hpp"
#include "log.hpp"
#include "style.hpp"
#include "benchmark.hpp"


#define FONT_SIZE 18.0f

#define CURSOR(cursor) \
if (IsItemHovered()) SetMouseCursor(cursor);

#define SELECTABLE(name, condition) \
Selectable(((name + (condition ? "(*)" : "")).c_str())) && !condition

#define GRAYSCALE(value) \
{value, value, value, 1.0f}

#define NEXT_WINDOW_DIM(x) \
SetNextWindowPos(LAYOUT_POS(x)); \
SetNextWindowSize(LAYOUT_SIZE(x));


static void set_theme();
static void new_frame();
static void render_draw_data();

static std::vector<str> get_scenes();


using namespace ImGui;


namespace Asagao
{
    Interface::Interface()
    //        wow
    : m_views
      {
          [this]() { this->startup_view(); },
          [this]() { this->scene_view();   }
      }
    , painting_tilemap{0}
    ,         selected{nullptr}
    {
        IMGUI_CHECKVERSION();

        CreateContext();
        StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(Window.handle, true);
        ImGui_ImplOpenGL3_Init();

        LOG_INFO(str("ImGui ") + IMGUI_VERSION);

        io = &(GetIO());
        io->IniFilename = nullptr;

        set_theme();
        load_fonts();
    }

    Interface::~Interface()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        DestroyContext();
    }

    void
    Interface::load_fonts()
    {
        io->Fonts->Clear();

        io->Fonts->AddFontFromFileTTF
        (
            "resources\\fonts\\adobe\\SourceCodePro-Regular.ttf",
            FONT_SIZE
        );

        f32 icon_size = FONT_SIZE * 2.0f / 3.0f;

        ImFontConfig icon_config;
        icon_config.MergeMode        = true;
        icon_config.PixelSnapH       = true;
        icon_config.GlyphMinAdvanceX = FONT_SIZE;
        icon_config.GlyphOffset.y    = 0.75f;

        static const ImWchar icon_range[] = {ICON_MIN_FA, ICON_MAX_16_FA, 0};

        io->Fonts->AddFontFromFileTTF
        (
            "resources\\fonts\\FA6\\" FONT_ICON_FILE_NAME_FAS,
            FONT_SIZE,
            &icon_config,
            icon_range
        );
    }

    void
    Interface::draw()
    {
        // Benchmark _("Interface render");

        new_frame();
        m_views[current_view]();
        render_draw_data();
    }

    void
    Interface::startup_view()
    {
        static c_cstr title = " " ICON_FA_FOLDER_OPEN "  Select a scene";
        static const ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove
            | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
        static const ImVec2 pad = {0.0f, 0.0f};
        static const ImVec2 pos = {0.0f, 0.0f};
        static bool hover;

        // static const std::vector<str> scenes = get_scenes();

        NEXT_WINDOW_DIM(Layout::start)

        Begin(title, nullptr, flags);

        PushStyleVar(ImGuiStyleVar_FramePadding, {20.0f, 15.0f});

        if (Button((ICON_FA_SQUARE_PLUS " New scene")))
            Application.scene = std::make_unique<Scene>();
        CURSOR(ImGuiMouseCursor_Hand)

        /*
        Dummy(pad);
        Separator();
        Dummy(pad);

        for (const auto& scene : scenes)
        {
            if (Button((ICON_FA_MOUNTAIN_SUN " " + scene).c_str()))
                Application.scene = std::make_unique<Scene>(scene);
            CURSOR(ImGuiMouseCursor_Hand)
        }
        */

        PopStyleVar();

        End();
    }

    void
    Interface::objects()
    {
        static c_cstr title = " " ICON_FA_LIST_UL "  Scene Objects";
        static const ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove
            | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
        static const ImVec2 row = {0.0f, FONT_SIZE};
        static bool is_selected;
        static u16  i, j, ts_i, go_i;

        NEXT_WINDOW_DIM(Layout::objects)

        if (painting_tilemap)
        {
            Begin(" " ICON_FA_PAINTBRUSH "  TileSet Layer Editor", nullptr, flags);

            Text("wip"); //Application.scene->assets..tile_set_layers[Application.scene->current_tilemap - 1].name.c_str());
            Dummy(row);

            if (Button("Exit TileSet painting mode"))
                painting_tilemap = 0;
            CURSOR(ImGuiMouseCursor_Hand)

            End();
            return;
        }

        Begin(title, nullptr, flags);

        if (BeginPopupContextWindow("new object menu", ImGuiPopupFlags_MouseButtonRight))
        {
            if (Button("New GameObject"))
            {
                Application.scene->assets.tile_sets[DEFAULT_TILESET].game_objects.emplace_back
                (
                    GameObject
                    (
                        "GameObject " + GameObject::get_new_number(),
                        v3(0.0f),
                        0.0f,
                        v3(1.0f),
                        0.0f,
                        true,
                        1,
                        {{12, 0}}
                    )
                );

                if (!io->KeyShift)
                    CloseCurrentPopup();
            }
            CURSOR(ImGuiMouseCursor_Hand)

            if (Button("New TileSet"))
            {
                Application.scene->assets.tile_sets[DEFAULT_TILESET].tile_set_layers.emplace_back
                (
                    TileSetLayer("TileSet Layer " + TileSetLayer::get_new_number())
                );

                if (!io->KeyShift)
                    CloseCurrentPopup();
            }
            CURSOR(ImGuiMouseCursor_Hand)

            EndPopup();
        }

        i    = 0;
        ts_i = 0;

        // temp sorted only by tile sets (later use pointers/indices)
        for (auto& ts : Application.scene->assets.tile_sets)
        {
            go_i = 0;

            for (auto go_it = ts.game_objects.begin(); go_it != ts.game_objects.end(); /**/)
            {
                is_selected = (&(*go_it) == selected);

                if (SELECTABLE(ICON_FA_CUBE " " + go_it->name, is_selected))
                {
                    selected         = &(*go_it);
                    selected_type    = AsagaoType::GameObject;
                    selected_tileset = ts_i;
                    selected_i       = go_i;
                }

                if (BeginPopupContextItem(("go" + std::to_string(i++)).c_str(), ImGuiPopupFlags_MouseButtonRight))
                {
                    if (Button("Delete"))
                    {
                        if (is_selected)
                            selected = nullptr;

                        go_it = ts.game_objects.erase(go_it);

                        CloseCurrentPopup();
                    }
                    else
                        ++go_it;
                    CURSOR(ImGuiMouseCursor_Hand)

                    EndPopup();
                }
                else
                    ++go_it;

                ++go_i;
            }

            ++ts_i;
        }

        j = 0;

        // same here, also temp 2 loops over the same vector
        for (auto& ts : Application.scene->assets.tile_sets)
        {
            i = 0;

            for (auto tm_it = ts.tile_set_layers.begin(); tm_it != ts.tile_set_layers.end(); /**/)
            {
                is_selected = (&(*tm_it) == selected);

                if (SELECTABLE(ICON_FA_TABLE_CELLS " " + tm_it->name, is_selected))
                {
                    selected      = &(*tm_it);
                    selected_type = AsagaoType::TileSetLayer;
                }

                if (BeginPopupContextItem(("tm" + std::to_string(i++)).c_str(), ImGuiPopupFlags_MouseButtonRight))
                {
                    if (Button("Edit"))
                    {
                        // yes, after i++, here the index goes from 1 so it can be used as a boolean
                        painting_tilemap = i;
                        painting_tileset = j;  // screaming for a reimplementation

                        CloseCurrentPopup();
                    }
                    CURSOR(ImGuiMouseCursor_Hand)

                    if (Button("Delete"))
                    {
                        if (is_selected)
                            selected = nullptr;

                        tm_it = ts.tile_set_layers.erase(tm_it);

                        CloseCurrentPopup();
                    }
                    else
                        ++tm_it;
                    CURSOR(ImGuiMouseCursor_Hand)

                    EndPopup();
                }
                else
                    ++tm_it;
            }

            ++j;
        }

        Dummy(row);

        End();
    }

    void
    Interface::assets()
    {
        static c_cstr title = " " ICON_FA_FILL_DRIP "  Assets";
        static const ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove
            | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
        static const ImVec2 row = {0.0f, FONT_SIZE};
        static bool is_selected;
        static u16  i;

        NEXT_WINDOW_DIM(Layout::assets)

        Begin(title, nullptr, flags);

        if (BeginPopupContextWindow("new asset menu", ImGuiPopupFlags_MouseButtonRight))
        {
            if (Button("New TileSet"))
            {
                Application.scene->assets.tile_sets.emplace_back
                (
                    // temp, later from a filesystem dialog 
                    TileSet("red-bubble.png", 8)
                );

                if (!io->KeyShift)
                    CloseCurrentPopup();
            }
            CURSOR(ImGuiMouseCursor_Hand)

            EndPopup();
        }

        i = 0;

        // always >0 since there is a hidden default one
        if (Application.scene->assets.tile_sets.size() - 1 && CollapsingHeader("TileSets"))
        {
            // same reason    vvvvvvvvv
            for (auto ts_it = std::next(Application.scene->assets.tile_sets.begin()); ts_it != Application.scene->assets.tile_sets.end(); /**/)
            {
                is_selected = (&(*ts_it) == selected);

                if (SELECTABLE(ICON_FA_TABLE_CELLS " " + ts_it->name, is_selected))
                {
                    selected      = &(*ts_it);
                    selected_type = AsagaoType::TileSet;
                }

                if (BeginPopupContextItem(("ts" + std::to_string(i++)).c_str(), ImGuiPopupFlags_MouseButtonRight))
                {
                    if (Button("Delete"))
                    {
                        if (is_selected)
                            selected = nullptr;

                        ts_it = Application.scene->assets.tile_sets.erase(ts_it);

                        CloseCurrentPopup();
                    }
                    else
                        ++ts_it;
                    CURSOR(ImGuiMouseCursor_Hand)

                    EndPopup();
                }
                else
                    ++ts_it;
            }
        }

        Dummy(row);

        End();
    }

    void
    Interface::details
    (v2& hovered_tile)
    {
        static c_cstr title = "Details";
        static const ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove;
        static const f32    button_height   = GetItemRectSize().y;
        static const ImVec2 window_padding  = {0.00f, 0.00f};
        static const ImVec4 button_color    = {0.15f, 0.15f, 0.15f, 1.0f};

        static v2 camera_pos, mouse_pos, world_pos;
        static bool hover;

        SetNextWindowPos
        ({
            Layout::objects.size.x * Window.size.x,
            Window.size.y - button_height
        });
        SetNextWindowSize
        ({
            Layout::scene.size.x * Window.size.x,
            button_height
        });

        PushStyleVar(ImGuiStyleVar_WindowPadding, window_padding);
        PushStyleColor(ImGuiCol_WindowBg, button_color);

        Begin(title, nullptr, flags);

        if (Button((ICON_FA_MOUNTAIN_SUN " " + Application.scene->name).c_str()))
        {
            Application.scene->unload();

            End();

            PopStyleColor();
            PopStyleVar();

            return;
        }
        CURSOR(ImGuiMouseCursor_Hand)

        SameLine();
        TextDisabled("|");
        SameLine();

        Text
        (
            (
                ICON_FA_MAGNIFYING_GLASS " "
                + std::to_string((i32) (1.0f / Renderer.zoom * 100))
                + "%%"
            ).c_str()
        );

        SameLine();
        TextDisabled("|");
        SameLine();

        camera_pos = Camera.get_position();

        Text
        (
            (
                ICON_FA_CAMERA " "
                + std::to_string((i32) camera_pos.x)
                + ", "
                + std::to_string((i32) camera_pos.y)
            ).c_str()
        );

        if (Window.mouse_hovers_scene())
        {
            // todo: zoom
            mouse_pos  = Window.mouse_pos;
            mouse_pos -= Window.size * 0.5f;

            world_pos    = mouse_pos;
            world_pos   -= camera_pos * 0.5f;
            world_pos.y += camera_pos.y;  // workaround(?)

            hovered_tile  = world_pos;
            hovered_tile /= Application.rect_size * 0.5f;
            hovered_tile += 0.5f;

            hovered_tile = {std::floor(hovered_tile.x), std::floor(hovered_tile.y)};

            SameLine();
            TextDisabled("|");
            SameLine();

            Text
            (
                (
                    ICON_FA_ARROW_POINTER " "
                    + std::to_string((i32) mouse_pos.x)
                    + ", "
                    + std::to_string((i32) mouse_pos.y)
                ).c_str()
            );

            SameLine();
            TextDisabled("|");
            SameLine();

            Text
            (
                (
                    ICON_FA_GLOBE " "
                    + std::to_string((i32) world_pos.x)
                    + ", "
                    + std::to_string((i32) world_pos.y)
                ).c_str()
            );

            SameLine();
            TextDisabled("|");
            SameLine();

            Text
            (
                (
                    ICON_FA_SQUARE " "
                    + std::to_string((i32) hovered_tile.x)
                    + ", "
                    + std::to_string((i32) hovered_tile.y)
                ).c_str()
            );
        }

        End();

        PopStyleColor();
        PopStyleVar();
    }

    void
    Interface::settings()
    {
        static c_cstr title = " " ICON_FA_GEAR "  Settings";
        static const ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove
            | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;

        Begin(title, nullptr, flags);

        DragFloat("Animation speed", &Application.animation_speed, 0.01f);  // will be obj-specific later

        End();
    }

    void
    Interface::inspector()
    {
        static c_cstr title = " " ICON_FA_MAGNIFYING_GLASS "  Inspector";
        static const ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove
            | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
        static const f32 close_btn = CalcTextSize("   ").x;
        static const ImVec2 row = {0.0f, FONT_SIZE};

        NEXT_WINDOW_DIM(Layout::inspector)

        if (!selected)
        {
            settings();
            return;
        }

        Begin(title, nullptr, flags);

        switch (selected_type)
        {
            // c++20: using enum AsagaoType;
        // Objects
        case AsagaoType::GameObject:
        {
            static std::string tag;

            auto& obj = Application.scene->assets.tile_sets[selected_tileset].game_objects[selected_i];

            const char* obj_ts = Application.scene->assets.tile_sets[selected_tileset].name.c_str();
            u16 ts_i = 0;

            static int new_offset[2] = {0, 0};

            Text(obj.name.c_str());

            SameLine(GetWindowContentRegionMax().x - close_btn);

            if (Button(ICON_FA_XMARK))
            {
                selected = nullptr;

                End();   // maybe a goto for all things like this? T_T
                return;  //
            }
            CURSOR(ImGuiMouseCursor_Hand)

            Separator();

            InputText("Tag", &tag);

            SameLine();

            if (Button("Save") && !tag.empty())
                Application.scene->hashed_objects[tag.c_str()] = {selected_tileset, selected_i};
            CURSOR(ImGuiMouseCursor_Hand)

            Separator();

            Text("Tileset");

            SameLine();

            if (BeginCombo("##gameobj's ts", obj_ts))
            {
                for (auto& ts : Application.scene->assets.tile_sets)
                {
                    if (Selectable(ts.name.c_str()) && ts_i != selected_tileset)
                    {
                        auto& old = Application.scene->assets.tile_sets[selected_tileset].game_objects;
                        old.erase(old.begin() + selected_i);

                        selected_i       = ts.game_objects.size();
                        selected_tileset = ts_i;

                        ts.game_objects.emplace_back(obj);  // maybe std::move?
                        selected = &(ts.game_objects.back());  // stop using this void* eventually
                                                               // and just add AsagaoType::None
                        obj = *(static_cast<GameObject*>(selected));
                    }

                    ++ts_i;
                }

                EndCombo();
            }

            Separator();

            Text("Tile offsets");

            SameLine();

            if (Button("Reset"))
            {
                obj.sprite_offsets = {{!selected_tileset * 12, 0}};
                obj.sprite_count   = 1;
            }
            CURSOR(ImGuiMouseCursor_Hand)
            
            InputInt2("##new tile offset", new_offset);

            SameLine();

            if (Button("Append"))
            {
                obj.sprite_offsets.emplace_back(v2(new_offset[0], new_offset[1]));
                ++obj.sprite_count;
            }
            CURSOR(ImGuiMouseCursor_Hand)

            Dummy(row);

            if (BeginTable("lol tile offsets", 2, ImGuiTableFlags_RowBg))
            {
                TableSetupColumn("x##tile offset");
                TableSetupColumn("y##tile offset");
                TableHeadersRow();

                for (const auto& offset : obj.sprite_offsets)
                {
                    TableNextRow();

                    TableSetColumnIndex(0);
                    Text("%g", offset.x);
                    TableSetColumnIndex(1);
                    Text("%g", offset.y);
                }

                EndTable();
            }

            break;
        }
        case AsagaoType::TileSetLayer:
        {
            auto obj = static_cast<TileSetLayer*>(selected);
            Text(obj->name.c_str());
            break;
        }
        // Assets
        case AsagaoType::TileSet:
        {
            auto obj = static_cast<TileSet*>(selected);
            Text(obj->name.c_str());
            break;
        }
        default:
            LOG_ERROR("unknown selected object type");

            selected = nullptr;

            End();
            return;
        }

        End();
    }

    void
    Interface::scene_view()
    {
        static v2 last_dragged_tile(0.5f);  // not round for the first comparison
        static v2 hovered_tile;

        objects();
        assets();
        details(hovered_tile);

        // here because details can unload the current scene
        if (!Application.scene)
            return;

        inspector();

        if
        (
            painting_tilemap
            && IsMouseDown(ImGuiMouseButton_Right)
            && hovered_tile != last_dragged_tile
            && Window.mouse_hovers_scene()
        )
        {
            Application.scene->assets.tile_sets[painting_tileset].tile_set_layers[painting_tilemap - 1].paint(hovered_tile);

            last_dragged_tile = hovered_tile;
        }
    }
}  // Asagao::


static void
set_theme()
{
    auto& style = GetStyle();

    style.WindowBorderSize = 0.0f;

    auto colors = style.Colors;

    colors[ImGuiCol_TitleBg]              = GRAYSCALE(0.25f);
    colors[ImGuiCol_TitleBgActive]        = GRAYSCALE(0.25f);
    colors[ImGuiCol_WindowBg]             = GRAYSCALE(0.07f);

    colors[ImGuiCol_FrameBg]              = GRAYSCALE(0.15f);
    colors[ImGuiCol_FrameBgHovered]       = GRAYSCALE(0.25f);
    colors[ImGuiCol_FrameBgActive]        = GRAYSCALE(0.35f);

    colors[ImGuiCol_Text]                 = GRAYSCALE(1.00f);
    colors[ImGuiCol_CheckMark]            = GRAYSCALE(1.00f);

    colors[ImGuiCol_Button]               = GRAYSCALE(0.15f);
    colors[ImGuiCol_ButtonHovered]        = GRAYSCALE(0.25f);
    colors[ImGuiCol_ButtonActive]         = GRAYSCALE(0.35f);

    colors[ImGuiCol_ScrollbarGrab]        = GRAYSCALE(0.20f);
    colors[ImGuiCol_ScrollbarGrabHovered] = GRAYSCALE(0.30f);
    colors[ImGuiCol_ScrollbarGrabActive]  = GRAYSCALE(0.40f);

    colors[ImGuiCol_Header]               = GRAYSCALE(0.10f);
    colors[ImGuiCol_HeaderHovered]        = GRAYSCALE(0.15f);
    colors[ImGuiCol_HeaderActive]         = GRAYSCALE(0.25f);

    colors[ImGuiCol_SliderGrab]           = GRAYSCALE(0.35f);
    colors[ImGuiCol_SliderGrabActive]     = GRAYSCALE(0.45f);

    colors[ImGuiCol_TableHeaderBg]        = GRAYSCALE(0.20f);
    colors[ImGuiCol_TableRowBg]           = GRAYSCALE(0.12f);
    colors[ImGuiCol_TableRowBgAlt]        = GRAYSCALE(0.16f);
}

static void
new_frame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    NewFrame();
}

static void
render_draw_data()
{
    Render();
    ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());
}

static std::vector<str>
get_scenes()
{
    namespace fs = std::filesystem;

    static const fs::path directory = "resources/scenes";
    static const str      extension = ".asagao";

    std::vector<str> scenes;

    for (const auto& entry : fs::directory_iterator(directory))
    {
        if (entry.is_regular_file() && entry.path().extension() == extension)
            scenes.emplace_back(entry.path().stem().string());
    }

    if (!scenes.size())
        LOG_WARN("no scenes found");

    return scenes;
}
