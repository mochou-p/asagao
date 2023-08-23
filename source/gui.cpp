// asagao/source/gui.cpp


#include <iostream>
#include "gui.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "window.hpp"
#include "style.hpp"

using namespace ImGui;

Gui::Gui()
{
    IMGUI_CHECKVERSION();
    CreateContext();
    StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(Window::handle, true);
    ImGui_ImplOpenGL3_Init();

    std::cout << "ImGui\t" << IMGUI_VERSION << std::endl;

    GetIO().IniFilename = nullptr;
}

Gui::~Gui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    DestroyContext();
}

inline static void new_frame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    NewFrame();
}

static void hierarchy()
{
    static const char*            title = "Hierarchy";
    static const ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;

    SetNextWindowPos
    ({
        Layout::hierarchy.pos.x * Window::width,
        Layout::hierarchy.pos.y * Window::height
    });
    SetNextWindowSize
    ({
        Layout::hierarchy.size.x * Window::width,
        Layout::hierarchy.size.y * Window::height
    });

    Begin(title, nullptr, flags);
    End();
}

static void scene()
{
    static const char*            title = "Scene";
    static const ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse
        | ImGuiWindowFlags_NoBackground;

    SetNextWindowPos
    ({
        Layout::scene.pos.x * Window::width,
        Layout::scene.pos.y * Window::height
    });
    SetNextWindowSize
    ({
        Layout::scene.size.x * Window::width,
        Layout::scene.size.y * Window::height
    });

    Begin(title, nullptr, flags);
    End();
}

static void inspector()
{
    static const char*            title = "Inspector";
    static const ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;

    SetNextWindowPos
    ({
        Layout::inspector.pos.x * Window::width,
        Layout::inspector.pos.y * Window::height
    });
    SetNextWindowSize
    ({
        Layout::inspector.size.x * Window::width,
        Layout::inspector.size.y * Window::height
    });

    Begin(title, nullptr, flags);
    End();
}

static void update_widgets()
{
    hierarchy();
    scene();
    inspector();
}

inline static void render_gui()
{
    Render();
    ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());
}

void Gui::draw()
{
    new_frame();
    update_widgets();
    render_gui();
}
