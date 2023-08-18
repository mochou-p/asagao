// asagao/source/gui.cpp


#include <iostream>
#include "gui.hpp"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "window.hpp"

using namespace ImGui;

Gui::Gui()
{
    IMGUI_CHECKVERSION();
    CreateContext();
    StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(Window::handle, true);
    ImGui_ImplOpenGL3_Init();

    std::cout << "ImGui\t" << IMGUI_VERSION << std::endl;
}

Gui::~Gui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    DestroyContext();
}

void new_frame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    NewFrame();
}

ImVec2 get_window_size()
{
    int width, height;
    glfwGetFramebufferSize(Window::handle, &width, &height);

    return {(float) width, (float) height};
}

void hierarchy()
{
    Begin("a", nullptr);
    End();
}

void scene()
{
    Begin("b", nullptr);
    End();
}

void inspector()
{
    Begin("c", nullptr);
    End();
}

void update_widgets()
{
    hierarchy();
    scene();
    inspector();
}

void render_gui()
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
