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


static void set_theme();
static void load_fonts();
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
    {
        IMGUI_CHECKVERSION();

        CreateContext();
        StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(Window.handle, true);
        ImGui_ImplOpenGL3_Init();

        LOG_INFO(str("ImGui ") + IMGUI_VERSION);

        GetIO().IniFilename = nullptr;

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

        static const std::vector<str> scenes = get_scenes();

        SetNextWindowPos(pos);
        SetNextWindowSize({Window.size.x, Window.size.y});

        Begin(title, nullptr, flags);

        PushStyleVar(ImGuiStyleVar_FramePadding, {20.0f, 15.0f});

        if (Button((ICON_FA_SQUARE_PLUS " New scene")))
            Application.scene = std::make_unique<Scene>();
        CURSOR(ImGuiMouseCursor_Hand)

        Dummy(pad);
        Separator();
        Dummy(pad);

        for (const auto& scene : scenes)
        {
            if (Button((ICON_FA_MOUNTAIN_SUN " " + scene).c_str()))
                Application.scene = std::make_unique<Scene>(scene);
            CURSOR(ImGuiMouseCursor_Hand)
        }

        PopStyleVar();

        End();
    }

    void
    Interface::objects()
    {
        static c_cstr title = " " ICON_FA_LIST_UL "  Scene Objects";
        static const ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove
            | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;

        static const ImVec4 darkened  = {1.00f, 1.00f, 1.00f, 0.4f};
        static const f32    close_btn = CalcTextSize("   ").x;
        static const ImVec2 row       = {0.0f, 10.0f};
        static bool is_selected;
        static u16  i;

        SetNextWindowPos
        ({
            Layout::objects.pos.x * Window.size.x,
            Layout::objects.pos.y * Window.size.y
        });
        SetNextWindowSize
        ({
            Layout::objects.size.x * Window.size.x,
            Layout::objects.size.y * Window.size.y
        });

        if (Application.scene->current_tilemap)
        {
            Begin(" " ICON_FA_PAINTBRUSH "  TileSet Layer Editor", nullptr, flags);

            Text(Application.scene->tilemaps[Application.scene->current_tilemap - 1].name.c_str());
            Dummy(row);

            if (Button("Exit TileSet painting mode"))
                Application.scene->current_tilemap = 0;

            End();
            return;
        }

        Begin(title, nullptr, flags);

        if (BeginPopupContextWindow("new object menu", ImGuiPopupFlags_MouseButtonRight))
        {
            if (Button("New GameObject"))
            {
                Application.scene->objects.emplace_back
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
                        {{
                            3 * Application.uv_fraction.x,
                            1 * Application.uv_fraction.y
                        }}
                    )
                );

                CloseCurrentPopup();
            }
            if (Button("New TileSet"))
            {
                Application.scene->tilemaps.emplace_back
                (
                    TileSetLayer("TileSet Layer " + TileSetLayer::get_new_number())
                );

                CloseCurrentPopup();
            }

            EndPopup();
        }

        i = 0;

        if (Application.scene->objects.size() && CollapsingHeader("GameObjects"))
        {
            for (auto go_it = Application.scene->objects.begin(); go_it != Application.scene->objects.end();)
            {
                is_selected = (&(*go_it) == Application.scene->selected);

                if (SELECTABLE(ICON_FA_CUBE " " + go_it->name, is_selected))
                    Application.scene->selected = &(*go_it);

                if (BeginPopupContextItem(("go" + std::to_string(i++)).c_str(), ImGuiPopupFlags_MouseButtonRight))
                {
                    if (Button("Delete"))
                    {
                        if (is_selected)
                            Application.scene->selected = nullptr;

                        go_it = Application.scene->objects.erase(go_it);

                        CloseCurrentPopup();
                    }
                    else
                        ++go_it;

                    EndPopup();
                }
                else
                    ++go_it;
            }
        }

        i = 0;

        if (Application.scene->tilemaps.size() && CollapsingHeader("TileSet Layers"))
        {
            for (auto tm_it = Application.scene->tilemaps.begin(); tm_it != Application.scene->tilemaps.end();)
            {
                is_selected = (&(*tm_it) == Application.scene->selected);

                if (SELECTABLE(ICON_FA_TABLE_CELLS " " + tm_it->name, is_selected))
                    Application.scene->selected = &(*tm_it);

                if (BeginPopupContextItem(("tm" + std::to_string(i++)).c_str(), ImGuiPopupFlags_MouseButtonRight))
                {
                    if (Button("Edit"))
                    {
                        // yes, after i++, here the index goes from 1 so it can be used as a boolean
                        Application.scene->current_tilemap = i;

                        CloseCurrentPopup();
                    }

                    if (Button("Delete"))
                    {
                        if (is_selected)
                            Application.scene->selected = nullptr;

                        tm_it = Application.scene->tilemaps.erase(tm_it);

                        CloseCurrentPopup();
                    }
                    else
                        ++tm_it;

                    EndPopup();
                }
                else
                    ++tm_it;
            }
        }

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
    Interface::components()
    {
        static c_cstr titles[2]
        {
            " " ICON_FA_GEAR "  Settings",
            " " ICON_FA_PUZZLE_PIECE "  Components"
        };
        static const ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove
            | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
        static const f32    close_btn = CalcTextSize("   ").x;
        static const ImVec2 row       = {0.0f, 10.0f};
        static bool hover;
        static void* obj;

        if (!Application.scene)
            return;

        obj = Application.scene->selected;

        SetNextWindowPos
        ({
            Layout::components.pos.x * Window.size.x,
            Layout::components.pos.y * Window.size.y
        });
        SetNextWindowSize
        ({
            Layout::components.size.x * Window.size.x,
            Layout::components.size.y * Window.size.y
        });

        if (!obj)
        {
            Begin(titles[0], nullptr, flags);
            DragFloat("Anim speed", &Application.animation_speed, 0.1f, 0.0f, 100.0f);
            CURSOR(ImGuiMouseCursor_ResizeEW)

            End();
            return;
        }

        Begin(titles[1], nullptr, flags);
        /*
        Checkbox("##visible", &obj->visible);
        SameLine();
        InputText("##name", &obj->name);
        SameLine(GetWindowContentRegionMax().x - close_btn);

        if (Button(ICON_FA_XMARK))
        {
            Application.scene->selected = nullptr;

            End();
            return;
        }
        CURSOR(ImGuiMouseCursor_Hand)

        Dummy(row);

        Text(ICON_FA_SLIDERS " Position");
        DragFloat(ICON_FA_LEFT_RIGHT "##pos", &obj->position.x, 1.0f); CURSOR(ImGuiMouseCursor_ResizeEW)
        DragFloat(ICON_FA_UP_DOWN    "##pos", &obj->position.y, 1.0f); CURSOR(ImGuiMouseCursor_ResizeEW)
        DragFloat(ICON_FA_LAYER_GROUP,        &obj->depth,      0.2f); CURSOR(ImGuiMouseCursor_ResizeEW)
        if (obj->depth != 0.0f)
        {
            SameLine();
            if (Button(ICON_FA_ROTATE_LEFT "##depth"))
                obj->depth = 0.0f;
            CURSOR(ImGuiMouseCursor_Hand)
        }

        Dummy(row);

        Text(ICON_FA_SLIDERS " Size");
        DragFloat(ICON_FA_LEFT_RIGHT "##size", &obj->scale.x, 0.01f); CURSOR(ImGuiMouseCursor_ResizeEW)
        if (obj->scale.x != 1.0f)
        {
            SameLine();
            if (Button(ICON_FA_ROTATE_LEFT "##size.x"))
                obj->scale.x = 1.0f;
            CURSOR(ImGuiMouseCursor_Hand)
        }

        DragFloat(ICON_FA_UP_DOWN "##size", &obj->scale.y, 0.01f); CURSOR(ImGuiMouseCursor_ResizeEW)
        if (obj->scale.y != 1.0f)
        {
            SameLine();
            if (Button(ICON_FA_ROTATE_LEFT "##size.y"))
                obj->scale.y = 1.0f;
            CURSOR(ImGuiMouseCursor_Hand)
        }


        Dummy(row);

        Text(ICON_FA_SLIDERS " Rotation");
        SliderFloat(ICON_FA_ROTATE, &obj->rotation, 0.0f, 360.0f);
        if (obj->rotation != 0.0f)
        {
            SameLine();
            if (Button(ICON_FA_ROTATE_LEFT "##rotation"))
                obj->rotation = 0.0f;
            CURSOR(ImGuiMouseCursor_Hand)
        }

        */
        End();
    }

    void
    Interface::scene_view()
    {
        static v2 last_dragged_tile(0.5f);  // not round for the first comparison
        static v2 hovered_tile;

        objects();
        details(hovered_tile);
        components();

        // todo
        if
        (
            Application.scene->current_tilemap
            && IsMouseDown(ImGuiMouseButton_Right)
            && hovered_tile != last_dragged_tile
        )
        {
            Application.scene->tilemaps[Application.scene->current_tilemap - 1].paint(hovered_tile);

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

    colors[ImGuiCol_TitleBg]              = GRAYSCALE(0.13f);
    colors[ImGuiCol_TitleBgActive]        = GRAYSCALE(0.13f);
    colors[ImGuiCol_WindowBg]             = GRAYSCALE(0.00f);

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
}

static void
load_fonts()
{
    ImGuiIO& io = GetIO();

    io.Fonts->Clear();

    io.Fonts->AddFontFromFileTTF
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

    io.Fonts->AddFontFromFileTTF
    (
        "resources\\fonts\\FA6\\" FONT_ICON_FILE_NAME_FAS,
        FONT_SIZE,
        &icon_config,
        icon_range
    );
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
