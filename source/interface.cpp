// asagao/source/interface.cpp


#include "stdafx.h"

#include "asagao.hpp"

#include "game_object.hpp"
#include "log.hpp"
#include "style.hpp"
#include "benchmark.hpp"


#define FONT_SIZE 18.0f

#define CURSOR(x) \
if (IsItemHovered()) \
    SetMouseCursor(x);


static void set_theme();
static void load_fonts();
static void new_frame();
static void render_draw_data();
static void tilemap(const v2& hovered_tile);

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

        for (const str& scene : scenes)
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
        static c_cstr title = " " ICON_FA_LIST_UL "  Objects";
        static const ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove
            | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;

        static const ImVec4 darkened  = {1.00f, 1.00f, 1.00f, 0.4f};
        static const f32    close_btn = CalcTextSize("   ").x;
        static bool is_selected;

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

        Begin(title, nullptr, flags);

        for (GameObject& obj : Application.scene->objects)
        {
            is_selected = (&obj == Application.scene->selected);

            if (!obj.visible)
                PushStyleColor(ImGuiCol_Text, darkened);

            if
            (
                Selectable
                (
                    (
                        ICON_FA_CUBE " "
                        + obj.name
                        + (is_selected ? "(*)" : "")
                    ).c_str()
                )
                &&
                !is_selected
            )
            {
                Application.scene->selected = &obj;
            }
            if (!is_selected)
                CURSOR(ImGuiMouseCursor_Hand)

            if (!obj.visible)
                PopStyleColor();
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
        static const ImVec2 row      = {0.0f, 10.0f};
        static bool hover;
        static GameObject* obj;

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

        End();
    }

    void
    Interface::scene_view()
    {
        static v2 tile;

        objects();
        details(tile);
        components();

        // temp
        tilemap(tile);
    }
}  // Asagao::


static void
set_theme()
{
    ImGuiStyle& style = GetStyle();

    style.WindowBorderSize = 0.0f;

    ImVec4* colors = style.Colors;

    colors[ImGuiCol_TitleBg]              = {0.13f, 0.13f, 0.13f, 1.0f};
    colors[ImGuiCol_TitleBgActive]        = {0.13f, 0.13f, 0.13f, 1.0f};
    colors[ImGuiCol_WindowBg]             = {0.00f, 0.00f, 0.00f, 1.0f};

    colors[ImGuiCol_FrameBg]              = {0.15f, 0.15f, 0.15f, 1.0f};
    colors[ImGuiCol_FrameBgHovered]       = {0.25f, 0.25f, 0.25f, 1.0f};
    colors[ImGuiCol_FrameBgActive]        = {0.35f, 0.35f, 0.35f, 1.0f};

    colors[ImGuiCol_Text]                 = {1.00f, 1.00f, 1.00f, 1.0f};
    colors[ImGuiCol_CheckMark]            = {1.00f, 1.00f, 1.00f, 1.0f};

    colors[ImGuiCol_Button]               = {0.15f, 0.15f, 0.15f, 1.0f};
    colors[ImGuiCol_ButtonHovered]        = {0.25f, 0.25f, 0.25f, 1.0f};
    colors[ImGuiCol_ButtonActive]         = {0.35f, 0.35f, 0.35f, 1.0f};

    colors[ImGuiCol_ScrollbarGrab]        = {0.20f, 0.20f, 0.20f, 1.0f};
    colors[ImGuiCol_ScrollbarGrabHovered] = {0.30f, 0.30f, 0.30f, 1.0f};
    colors[ImGuiCol_ScrollbarGrabActive]  = {0.40f, 0.40f, 0.40f, 1.0f};

    colors[ImGuiCol_HeaderHovered]        = {0.15f, 0.15f, 0.15f, 1.0f};
    colors[ImGuiCol_HeaderActive]         = {0.25f, 0.25f, 0.25f, 1.0f};

    colors[ImGuiCol_SliderGrab]           = {0.35f, 0.35f, 0.35f, 1.0f};
    colors[ImGuiCol_SliderGrabActive]     = {0.45f, 0.45f, 0.45f, 1.0f};
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

struct pair_hash
{
    template<class T1, class T2>
    u64 operator()
    (const std::pair<T1, T2>& p) const
    {
        return std::hash<T1>{}(p.first) ^ std::hash<T2>{}(p.second);  
    }
};

static void
tilemap
(const v2& hovered_tile)
{
    using Tile    = std::pair<i32, i32>;
    using TileMap = std::unordered_map<Tile, bool, pair_hash>;
    // later a specific tiletype bitmask int ^^^^

    static TileMap           tiles;
    static TileMap::iterator it;
    static Tile              pair;

    static v2 last_dragged_tile(0.5f);  // not round for the first comparison

    static GameObject tile_obj
    (
        "----",
        v3(0.0f),
        0.0f,
        v3(1.0f),
        0.0f,
        true,
        1,
        {{
            1 * Asagao::Application.uv_fraction.x,
            3 * Asagao::Application.uv_fraction.y
        }}
    );

    if (IsMouseDown(ImGuiMouseButton_Right) && hovered_tile != last_dragged_tile)
    {
        pair = std::make_pair(hovered_tile.x, hovered_tile.y);
        it   = tiles.find(pair);

        if (it == tiles.end())
            tiles[pair] ^= 1;

        last_dragged_tile = hovered_tile;
    }

    for (const auto& kv : tiles)
    {
        tile_obj.position.x = kv.first.first  *  Asagao::Application.rect_size;
        tile_obj.position.y = kv.first.second * -Asagao::Application.rect_size;

        Asagao::Application.shader->set_mat4("u_mvp",     Asagao::Camera.get_mvp(tile_obj));
        Asagao::Application.shader->set_vec2("u_tile_uv", tile_obj.get_uv(0));

        Asagao::Renderer.draw();
    }
}
