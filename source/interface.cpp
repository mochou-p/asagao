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
using TilePos = std::pair<i32, i32>;
using TileMap = std::unordered_map<TilePos, TileUV, pair_hash>;

static TileUV
get_tile_rule
(const u8 mask)
{
    switch (mask)
    {
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

    case  24:
    case  25:
    case  28:
    case  29:
    case  56:
    case  57:
    case  60:
    case  61:
    case 152:
    case 153:
    case 189:
    case 184:
    case 185:
    case 156:
    case 188:
    case 157:
        return UV(0, 0);
    case  66:
    case  67:
    case  70:
    case  71:
    case  98:
    case  99:
    case 102:
    case 103:
    case 194:
    case 195:
    case 198:
    case 199:
    case 226:
    case 227:
    case 230:
    case 231:
        return UV(1, 0);

    case  80:
    case  81:
    case  84:
    case  85:
    case 112:
    case 113:
    case 116:
    case 117:
        return UV(3, 3);
    case  72:
    case  73:
    case  76:
    case  77:
    case 200:
    case 201:
    case 204:
    case 205:
        return UV(4, 3);
    case  18:
    case  19:
    case  50:
    case  51:
    case 146:
    case 147:
    case 178:
    case 179:
        return UV(3, 2);
    case  10:
    case  14:
    case  42:
    case  46:
    case 138:
    case 142:
    case 170:
    case 174:
        return UV(4, 2);

    case 120:
    case 121:
    case 124:
    case 125:
        return UV(5, 3);
    case 216:
    case 217:
    case 220:
    case 221:
        return UV(6, 3);
    case  27:
    case  59:
    case 155:
    case 187:
        return UV(5, 2);
    case  30:
    case  62:
    case 158:
    case 190:
        return UV(6, 2);

    case  86:
    case  87:
    case 118:
    case 119:
        return UV(5, 1);
    case  75:
    case  79:
    case 203:
    case 207:
        return UV(6, 1);
    case 210:
    case 211:
    case 242:
    case 243:
        return UV(5, 0);
    case 106:
    case 110:
    case 234:
    case 238:
        return UV(6, 0);

    case 122:
        return UV(7, 3);
    case 218:
        return UV(8, 3);
    case  91:
        return UV(7, 2);
    case  94:
        return UV(8, 2);

    case  82:
    case  83:
    case 114:
    case 115:
        return UV(7, 1);
    case  88:
    case  89:
    case  92:
    case  93:
        return UV(8, 1);
    case  26:
    case  58:
    case 154:
    case 186:
        return UV(7, 0);
    case  74:
    case  78:
    case 202:
    case 206:
        return UV(8, 0);

    case 127:
        return UV(11, 3);
    case 223:
        return UV(12, 3);
    case 251:
        return UV(11, 2);
    case 254:
        return UV(12, 2);

    case  90:
        return UV(10, 1);

    case  95:
        return UV(9, 3);
    case 222:
        return UV(10, 3);
    case 123:
        return UV(9, 2);
    case 250:
        return UV(10, 2);

    case 126:
        return UV(9, 1);
    case 219:
        return UV(9, 0);
    }

    // no need for a default case
}

static u8
neighbour_mask
(const v2& tile, const TileMap& tiles)
{
    u8 power = 0;
    u8 mask  = 0;

    // can be optimised
    for (i8 y = -1; y <= 1; ++y)
    {
        for (i8 x = -1; x <= 1; ++x)
        {
            if (x || y)
            {
                auto pair = std::make_pair(tile.x + x, tile.y + y);

                if (tiles.find(pair) != tiles.end())
                    mask += std::pow(2, power);

                ++power;
            }
        }
    }

    return mask;
}

static void
tilemap
(const v2& hovered_tile)
{
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
            tiles[pair] = get_tile_rule(neighbour_mask(hovered_tile, tiles));

            // for now updating all NOT EMPTY tiles around
            // can be optimised for only those who should change
            //     (for example, some dont change with diagonal updates)
            // and can be cached to not recalculate neighbours

            for (i8 y = -1; y <= 1; ++y)
            {
                for (i8 x = -1; x <= 1; ++x)
                {
                    if (x || y)
                    {
                        pair = std::make_pair(hovered_tile.x + x, hovered_tile.y + y);

                        if (tiles.find(pair) != tiles.end())
                            tiles[pair] = get_tile_rule(neighbour_mask(hovered_tile + v2(x, y), tiles));
                    }
                }
            }
        }

        last_dragged_tile = hovered_tile;
    }

    for (const auto& kv : tiles)
    {
        tile_obj.position.x = kv.first.first  *  Asagao::Application.rect_size;
        tile_obj.position.y = kv.first.second * -Asagao::Application.rect_size;

        tile_obj.sprite_offsets[0].x = kv.second.x;
        tile_obj.sprite_offsets[0].y = kv.second.y;

        Asagao::Renderer.draw(tile_obj);
    }
}
