// asagao/source/interface.cpp


#include "interface.hpp"

#include "window.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <cstdio>


static void new_frame();
static void render_draw_data();


Interface::Interface
(Window& window)
: r_window(window)
{
    std::printf("Interface\n");

    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGui::StyleColorsDark();
}

Interface::~Interface()
{
    std::printf("~Interface\n");

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    ImGui::DestroyContext();
}

void
Interface::init() const
{
    ImGui_ImplGlfw_InitForOpenGL(r_window.get_handle(), true);
    ImGui_ImplOpenGL3_Init();

    ImGui::GetIO().IniFilename = nullptr;
}

void
Interface::render() const noexcept
{
    new_frame();

    if (ImGui::Begin("Hello", nullptr))
        ImGui::Text("world");
    ImGui::End();

    render_draw_data();
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
    ImGui::EndFrame();
    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
