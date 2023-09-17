// asagao/source/interface.cpp


#include <filesystem>
#include "interface.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "window.hpp"
#include "style.hpp"
#include "application.hpp"
#include "renderer.hpp"
#include "log.hpp"
#include "game_object.hpp"
#include "image.hpp"
#include "IconsFontAwesome6.h"

#define FONT_SIZE 18.0f

namespace fs = std::filesystem; 

static void
set_theme()
{
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowBorderSize = 0.0f;

    ImVec4* colors = style.Colors;

    colors[ImGuiCol_TitleBg]          = {0.13f, 0.13f, 0.13f, 1.0f};
    colors[ImGuiCol_TitleBgActive]    = {0.13f, 0.13f, 0.13f, 1.0f};
    colors[ImGuiCol_WindowBg]         = {0.00f, 0.00f, 0.00f, 1.0f};

    colors[ImGuiCol_FrameBg]          = {0.15f, 0.15f, 0.15f, 1.0f};
    colors[ImGuiCol_FrameBgHovered]   = {0.25f, 0.25f, 0.25f, 1.0f};
    colors[ImGuiCol_FrameBgActive]    = {0.35f, 0.35f, 0.35f, 1.0f};

    colors[ImGuiCol_Text]             = {1.00f, 1.00f, 1.00f, 1.0f};
    colors[ImGuiCol_CheckMark]        = {1.00f, 1.00f, 1.00f, 1.0f};

    colors[ImGuiCol_Button]           = {0.15f, 0.15f, 0.15f, 1.0f};
    colors[ImGuiCol_ButtonHovered]    = {0.25f, 0.25f, 0.25f, 1.0f};
    colors[ImGuiCol_ButtonActive]     = {0.35f, 0.35f, 0.35f, 1.0f};

    colors[ImGuiCol_HeaderHovered]    = {0.15f, 0.15f, 0.15f, 1.0f};
    colors[ImGuiCol_HeaderActive]     = {0.25f, 0.25f, 0.25f, 1.0f};

    colors[ImGuiCol_Separator]        = {0.01f, 0.01f, 0.01f, 1.0f};
    colors[ImGuiCol_SeparatorHovered] = {0.01f, 0.01f, 0.01f, 1.0f};
    colors[ImGuiCol_SeparatorActive]  = {0.01f, 0.01f, 0.01f, 1.0f};

    colors[ImGuiCol_SliderGrab]       = {0.35f, 0.35f, 0.35f, 1.0f};
    colors[ImGuiCol_SliderGrabActive] = {0.45f, 0.45f, 0.45f, 1.0f};
}

static void
load_fonts()
{
    ImGuiIO& io = ImGui::GetIO();

    io.Fonts->Clear();

    io.Fonts->AddFontFromFileTTF
    (
        "resources\\fonts\\adobe\\SourceCodePro-Regular.ttf",
        FONT_SIZE
    );

    float icon_size = FONT_SIZE * 2.0f / 3.0f;

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

Interface::Interface()
: m_current_view{0}
//               wow
,        m_views{
                 [this]() { this->startup_view(); },
                 [this]() { this->scene_view();   }
                }
{
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(Window::handle, true);
    ImGui_ImplOpenGL3_Init();

    LOG_INFO(std::string("ImGui ") + IMGUI_VERSION);

    ImGui::GetIO().IniFilename = nullptr;
    set_theme();
    load_fonts();
}

Interface::~Interface()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

static void
new_frame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

static void
render_draw_data()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void
objects()
{
    using namespace ImGui;

    static const char* title = " " ICON_FA_LIST_UL "  Objects";
    static const ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;

    static const ImVec4 darkened  = {1.0f, 1.0f, 1.0f, 0.4f};
    static const float  close_btn = CalcTextSize("   ").x;

    SetNextWindowPos
    ({
        Layout::objects.pos.x * Window::size.x,
        Layout::objects.pos.y * Window::size.y
    });
    SetNextWindowSize
    ({
        Layout::objects.size.x * Window::size.x,
        Layout::objects.size.y * Window::size.y
    });

    Begin(title, nullptr, flags);

    for (GameObject& obj : Application::scene->objects)
    {
        if (!obj.visible) PushStyleColor(ImGuiCol_Text, darkened);

        if (Selectable((ICON_FA_CUBE " " + obj.name).c_str()))
            Application::scene->selected = &obj;

        if (!obj.visible) PopStyleColor();
    }

    End();
}

void
Interface::details()
{
    using namespace ImGui;

    static const char* title = "Details";
    static const ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove;
    static const float button_height    = GetItemRectSize().y;
    static const ImVec2 window_padding  = {0.0f, 0.0f};

    SetNextWindowPos
    ({
        Layout::objects.size.x * Window::size.x,
        Window::size.y - button_height
    });
    SetNextWindowSize
    ({
        Window::size.x - (Layout::objects.size.x + Layout::components.size.x),
        button_height
    });

    PushStyleVar(ImGuiStyleVar_WindowPadding, window_padding);

    Begin(title, nullptr, flags);

    if (Button((ICON_FA_MOUNTAIN_SUN " " + Application::scene->name).c_str()))
    {
        Application::scene = nullptr;
        m_current_view     = 0;

        End();
        PopStyleVar();
        return;
    }

    SameLine();

    TextDisabled("|");

    SameLine();

    Text
    (
        (
            (ICON_FA_MAGNIFYING_GLASS " ")
            + std::to_string((int) (1.0f / Renderer::zoom * 100))
            + "%%"
        ).c_str()
    );

    End();

    PopStyleVar();
}

static void
components()
{
    using namespace ImGui;

    static const char* titles[2]
    {
        " " ICON_FA_GEAR "  Settings",
        " " ICON_FA_PUZZLE_PIECE "  Components"
    };
    static const ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
    static const float close_btn = CalcTextSize("   ").x;

    if (!Application::scene) return;

    SetNextWindowPos
    ({
        Layout::components.pos.x * Window::size.x,
        Layout::components.pos.y * Window::size.y
    });
    SetNextWindowSize
    ({
        Layout::components.size.x * Window::size.x,
        Layout::components.size.y * Window::size.y
    });


    if (!Application::scene->selected)
    {
        Begin(titles[0], nullptr, flags);
        DragFloat("Anim speed", &Application::animation_speed, 0.1f,
            0.0f, 100.0f);

        End();
        return;
    }

    Begin(titles[1], nullptr, flags);

    Checkbox(Application::scene->selected->name.c_str(),
        &Application::scene->selected->visible);
    SameLine(GetWindowContentRegionMax().x - close_btn);

    if (Button(ICON_FA_XMARK))
    {
        Application::scene->selected = nullptr;

        End();
        return;
    }

    Separator();

    Text(ICON_FA_SLIDERS " Position");
    DragFloat(ICON_FA_LEFT_RIGHT "##pos", &Application::scene->selected->position.x, 1.0f);
    DragFloat(ICON_FA_UP_DOWN    "##pos", &Application::scene->selected->position.y, 1.0f);
    DragFloat(ICON_FA_LAYER_GROUP,        &Application::scene->selected->depth,      0.2f);

    Separator();

    Text(ICON_FA_SLIDERS " Size");
    DragFloat(ICON_FA_LEFT_RIGHT "##size", &Application::scene->selected->scale.x, 0.01f);
    DragFloat(ICON_FA_UP_DOWN    "##size", &Application::scene->selected->scale.y, 0.01f);

    Separator();

    Text(ICON_FA_SLIDERS " Rotation");
    SliderFloat(ICON_FA_ROTATE, &Application::scene->selected->rotation, 0.0f, 360.0f);

    End();
}

void
Interface::draw()
{
    new_frame();
    m_views[m_current_view]();
    render_draw_data();
}

static std::vector<std::string>
get_scenes()
{
    static const fs::path    directory = "resources/scenes";
    static const std::string extension = ".asagao";

    std::vector<std::string> scenes;

    for (const auto& entry : fs::directory_iterator(directory))
    {
        if (entry.is_regular_file() && entry.path().extension() == extension)
            scenes.emplace_back(entry.path().stem().string());
    }

    if (!scenes.size())
        LOG_WARN("no scenes found");

    return scenes;
}

void
Interface::startup_view()
{
    using namespace ImGui;

    static const char*            title = " " ICON_FA_FOLDER_OPEN "  Select a scene";
    static const ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
    static const ImVec2           pos   = {0.0f, 0.0f};

    static const std::vector<std::string> scenes = get_scenes();

    SetNextWindowPos(pos);
    SetNextWindowSize({Window::size.x, Window::size.y});

    Begin(title, nullptr, flags);

    PushStyleVar(ImGuiStyleVar_FramePadding, {20.0f, 15.0f});
    for (const std::string& scene : scenes)
    {
        if (Button((ICON_FA_MOUNTAIN_SUN " " + scene).c_str()))
        {
            Application::scene = std::make_unique<Scene>(scene);
            m_current_view     = 1;
        }
    }
    PopStyleVar();

    End();
}

void
Interface::scene_view()
{
    objects();
    details();
    components();
}
