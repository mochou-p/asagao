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

namespace fs = std::filesystem; 

static void
set_theme()
{
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowBorderSize = 0.0f;

    ImVec4* colors = style.Colors;
    colors[ImGuiCol_TitleBg]          = {0.3f, 0.3f, 0.3f, 1.0f};
    colors[ImGuiCol_TitleBgActive]    = {0.3f, 0.3f, 0.3f, 1.0f};
    colors[ImGuiCol_WindowBg]         = {0.2f, 0.2f, 0.2f, 1.0f};

    colors[ImGuiCol_FrameBg]          = {0.3f, 0.3f, 0.3f, 1.0f};
    colors[ImGuiCol_FrameBgHovered]   = {0.4f, 0.4f, 0.4f, 1.0f};
    colors[ImGuiCol_FrameBgActive]    = {0.5f, 0.5f, 0.5f, 1.0f};

    colors[ImGuiCol_CheckMark]        = {1.0f, 1.0f, 1.0f, 1.0f};

    colors[ImGuiCol_Button]           = {0.3f, 0.3f, 0.3f, 1.0f};
    colors[ImGuiCol_ButtonHovered]    = {0.4f, 0.4f, 0.4f, 1.0f};
    colors[ImGuiCol_ButtonActive]     = {0.5f, 0.5f, 0.5f, 1.0f};

    colors[ImGuiCol_HeaderHovered]    = {0.4f, 0.4f, 0.4f, 1.0f};
    colors[ImGuiCol_HeaderActive]     = {0.5f, 0.5f, 0.5f, 1.0f};

    colors[ImGuiCol_Separator]        = {0.5f, 0.5f, 0.5f, 1.0f};
    colors[ImGuiCol_SeparatorHovered] = {0.5f, 0.5f, 0.5f, 1.0f};
    colors[ImGuiCol_SeparatorActive]  = {0.5f, 0.5f, 0.5f, 1.0f};

    colors[ImGuiCol_SliderGrab]       = {0.6f, 0.6f, 0.6f, 1.0f};
    colors[ImGuiCol_SliderGrabActive] = {0.8f, 0.8f, 0.8f, 1.0f};
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
Interface::objects()
{
    using namespace ImGui;

    static const char*            title    = "Objects";
    static const ImGuiWindowFlags flags    = ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
    static const ImVec4           darkened = {1.0f, 1.0f, 1.0f, 0.4f};

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

    if (Button("Back"))
    {
        Application::scene = nullptr;
        m_current_view     = 0;

        End();
        return;
    }

    SameLine();
    Text(Application::scene->name.c_str());

    Separator();

    for (GameObject& obj : Application::scene->objects)
    {
        if (!obj.visible) PushStyleColor(ImGuiCol_Text, darkened);

        if (Selectable(obj.name.c_str()))
            Application::scene->selected = &obj;

        if (!obj.visible) PopStyleColor();
    }

    End();
}

static void
components()
{
    using namespace ImGui;

    static const char*                title     = "Components";
    static const ImGuiWindowFlags     flags     = ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
    static const float                close_btn = CalcTextSize("x ").x;

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

    Begin(title, nullptr, flags);

    if (!Application::scene->selected)
    {
        DragFloat("Anim speed", &Application::animation_speed, 0.1f,
            0.0f, 100.0f);

        End();
        return;
    }

    Checkbox(Application::scene->selected->name.c_str(),
        &Application::scene->selected->visible);
    SameLine(GetWindowContentRegionMax().x - close_btn);
    if (Button("x"))
    {
        Application::scene->selected = nullptr;

        End();
        return;
    }

    Separator();

    Text("Position");
    DragFloat("X##pos", &Application::scene->selected->position.x, 1.0f);
    DragFloat("Y##pos", &Application::scene->selected->position.y, 1.0f);
    DragFloat("Depth",  &Application::scene->selected->depth,      0.2f);

    Separator();

    Separator();

    Text("Size");
    DragFloat("X##size", &Application::scene->selected->scale.x, 0.01f);
    DragFloat("Y##size", &Application::scene->selected->scale.y, 0.01f);

    Separator();

    Text("Rotation");
    SliderFloat("Degrees", &Application::scene->selected->rotation,
        0.0f, 360.0f);

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

    static const char*            title = "Select a scene";
    static const ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
    static const ImVec2           pos   = {0.0f, 0.0f};

    static const std::vector<std::string> scenes = get_scenes();

    SetNextWindowPos(pos);
    SetNextWindowSize({Window::size.x, Window::size.y});

    Begin(title, nullptr, flags);

    for (const std::string& scene : scenes)
    {
        if (Button(scene.c_str()))
        {
            Application::scene = std::make_unique<Scene>(scene);
            m_current_view     = 1;
        }
    }

    End();
}

void
Interface::scene_view()
{
    objects();
    components();
}

static void
tilemap_view()
{
    // todo: get here from right click on a tilemap and change m_current_view there

    using namespace ImGui;

    static const Texture     texture("atlases/kenney_pixel-platformer.png", false);
    static const ImTextureID tex_slot = (void*) texture.get_slot();
    static const ImVec2      tex_size = {texture.get_size().x, texture.get_size().y};

    ImGui::Begin("Tile selector", nullptr);
        ImGui::Image(tex_slot, tex_size);
    ImGui::End();
}
