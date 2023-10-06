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

// temp ----

#define UV(u, v) v2(u, v) * Asagao::Application.uv_fraction

struct pair_hash
{
    template<class T1, class T2>
    u64 operator()
    (const std::pair<T1, T2>& p) const
    {
        return std::hash<T1>{}(p.first) ^ std::hash<T2>{}(p.second);  
    }
};

using TileUV = v2;

static TileUV
get_tile_rule
(const u8 mask)
{
    switch (mask)
    {
    // ┌  ─  ┐
    case 208:
    case 209:
    case 212:
    case 213:
    case 240:
    case 241:
    case 244:
    case 245:
        return UV(0, 3);
    case 248:
    case 249:
    case 252:
    case 253:
        return UV(1, 3);
    case 104:
    case 105:
    case 108:
    case 109:
    case 232:
    case 233:
    case 236:
    case 237:
        return UV(2, 3);

    // │     │
    case 214:
    case 215:
    case 246:
    case 247:
        return UV(0, 2);
    case 255:
        return UV(1, 2);
    case 107:
    case 111:
    case 235:
    case 239:
        return UV(2, 2);

    // └  ─  ┘
    case  22:
    case  23:
    case  54:
    case  55:
    case 150:
    case 151:
    case 182:
    case 183:
        return UV(0, 1);
    case  31:
    case  63:
    case 159:
    case 191:
        return UV(1, 1);
    case  11:
    case  15:
    case  43:
    case  47:
    case 139:
    case 143:
    case 171:
    case 175:
        return UV(2, 1);

    // []
    case   0:
    case   1:
    case   4:
    case   5:
    case  32:
    case  33:
    case  36:
    case  37:
    case 128:
    case 129:
    case 132:
    case 133:
    case 160:
    case 161:
    case 164:
    case 165:
        return UV(3, 1);
    // [
    case  16:
    case  17:
    case  20:
    case  21:
    case  48:
    case  49:
    case  52:
    case  53:
    case 144:
    case 145:
    case 148:
    case 149:
    case 176:
    case 177:
    case 180:
    case 181:
        return UV(2, 0);
    // ]
    case   8:
    case   9:
    case  12:
    case  13:
    case  40:
    case  41:
    case  44:
    case  45:
    case 136:
    case 137:
    case 140:
    case 141:
    case 168:
    case 169:
    case 172:
    case 173:
        return UV(3, 0);
    // ┌─┐
    case  64:
    case  65:
    case  68:
    case  69:
    case  96:
    case  97:
    case 100:
    case 101:
    case 192:
    case 193:
    case 196:
    case 197:
    case 224:
    case 225:
    case 228:
    case 229:
        return UV(4, 1);
    // └─┘
    case   2:
    case   3:
    case   6:
    case   7:
    case  34:
    case  35:
    case  38:
    case  39:
    case 130:
    case 131:
    case 134:
    case 135:
    case 162:
    case 163:
    case 166:
    case 167:
        return UV(4, 0);

    // =
    case 24:
        return UV(0, 0);
    // ||
    case 66:
        return UV(1, 0);

    // ┌┐
    // └┘
    case  80:
    case  81:
    case  85:
    case 113:
    case 116:
    case 117:
        return UV(3, 3);
    case  72:
        return UV(4, 3);
    case  18:
        return UV(3, 2);
    case  10:
        return UV(4, 2);


    // ┴
    // ┬
    // ├
    // ┼
    // ┤

    default:
        LOG_WARN(std::to_string(mask));
        return UV(10, 0);
    }
}

static void
tilemap
(const v2& hovered_tile)
{
    using TilePos = std::pair<i32, i32>;
    
    using TileMap = std::unordered_map<TilePos, TileUV, pair_hash>;

    static TileMap tiles;
    static TilePos pair;

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
        {{0, 0}}
    );

    if (IsMouseDown(ImGuiMouseButton_Right) && hovered_tile != last_dragged_tile)
    {
        pair = std::make_pair(hovered_tile.x, hovered_tile.y);

        if (tiles.find(pair) == tiles.end())
        {
            u8 z             = 0;
            u8 neighbour_sum = 0;

            // todo optimise
            for (i8 y = -1; y <= 1; ++y)
            {
                for (i8 x = -1; x <= 1; ++x)
                {
                    if (x || y)
                    {
                        auto _pair = std::make_pair(hovered_tile.x + x, hovered_tile.y + y);

                        if (tiles.find(_pair) != tiles.end())
                            neighbour_sum += std::pow(2, z);

                        ++z;
                    }
                }
            }

            tiles[pair] = get_tile_rule(neighbour_sum);
        }

        last_dragged_tile = hovered_tile;
    }

    for (const auto& kv : tiles)
    {
        tile_obj.position.x = kv.first.first  *  Asagao::Application.rect_size;
        tile_obj.position.y = kv.first.second * -Asagao::Application.rect_size;

        tile_obj.sprite_offsets[0].x = kv.second.x;
        tile_obj.sprite_offsets[0].y = kv.second.y;

        Asagao::Application.shader->set_mat4("u_mvp",     Asagao::Camera.get_mvp(tile_obj));
        Asagao::Application.shader->set_vec2("u_tile_uv", tile_obj.get_uv(0));

        Asagao::Renderer.draw();
    }
}
