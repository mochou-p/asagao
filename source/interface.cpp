// asagao/source/interface.cpp


#include <iostream>
#include "interface.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "window.hpp"
#include "style.hpp"
#include "application.hpp"

using namespace ImGui;

static void
set_theme()
{
    ImGuiStyle& style = GetStyle();
    style.WindowBorderSize = 0.0f;

    ImVec4* colors = style.Colors;
    colors[ImGuiCol_TitleBg]        = {0.3f, 0.3f, 0.3f, 1.0f};
    colors[ImGuiCol_TitleBgActive]  = {0.3f, 0.3f, 0.3f, 1.0f};
    colors[ImGuiCol_WindowBg]       = {0.2f, 0.2f, 0.2f, 1.0f};

    colors[ImGuiCol_FrameBg]        = {0.3f, 0.3f, 0.3f, 1.0f};
    colors[ImGuiCol_FrameBgHovered] = {0.4f, 0.4f, 0.4f, 1.0f};
    colors[ImGuiCol_FrameBgActive]  = {0.5f, 0.5f, 0.5f, 1.0f};

    colors[ImGuiCol_CheckMark]      = {1.0f, 1.0f, 1.0f, 1.0f};

    colors[ImGuiCol_Button]         = {0.3f, 0.3f, 0.3f, 1.0f};
    colors[ImGuiCol_ButtonHovered]  = {0.4f, 0.4f, 0.4f, 1.0f};
    colors[ImGuiCol_ButtonActive]   = {0.5f, 0.5f, 0.5f, 1.0f};
}

Interface::Interface()
{
    IMGUI_CHECKVERSION();

    CreateContext();
    StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(Window::handle, true);
    ImGui_ImplOpenGL3_Init();

    std::cout << "ImGui\t" << IMGUI_VERSION << std::endl;

    GetIO().IniFilename = nullptr;
    set_theme();
}

Interface::~Interface()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    DestroyContext();
}

static void
new_frame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    NewFrame();
}

static void
objects()
{
    static const char*            title = "Objects";
    static const ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
    static GLuint i;
    static bool _ = true;

    SetNextWindowPos
    ({
        Layout::objects.pos.x * Window::width,
        Layout::objects.pos.y * Window::height
    });
    SetNextWindowSize
    ({
        Layout::objects.size.x * Window::width,
        Layout::objects.size.y * Window::height
    });

    Begin(title, nullptr, flags);

    for (i = 0; i < Application::objects.size(); ++i)
    {
        Checkbox("##_", &_);
        SameLine();
        Button(Application::objects[i]);
    }

    End();
}

static void
components()
{
    static const char*            title = "Components";
    static const ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;

    SetNextWindowPos
    ({
        Layout::components.pos.x * Window::width,
        Layout::components.pos.y * Window::height
    });
    SetNextWindowSize
    ({
        Layout::components.size.x * Window::width,
        Layout::components.size.y * Window::height
    });

    Begin(title, nullptr, flags);
    End();
}

static void
update_widgets()
{
    objects();
    components();
}

static void
render_draw_data()
{
    Render();
    ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());
}

void
Interface::draw() const
{
    new_frame();
    update_widgets();
    render_draw_data();
}
