// asagao/source/gui.cpp


#include "gui.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

using namespace ImGui;

Gui::Gui(GLFWwindow* t_window_handle)
{
    IMGUI_CHECKVERSION();
    CreateContext();
    StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(t_window_handle, true);
    ImGui_ImplOpenGL3_Init();
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

void update_widgets()
{
    static char title[] = "hi";

    Begin(title, nullptr);
    End();
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
