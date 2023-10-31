// asagao/source/interface.cpp


#include "interface.hpp"

#include "window.hpp"
#include "editor.hpp"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <cstdio>


static void new_frame()        noexcept;
static void render_draw_data() noexcept;


Interface::Interface
(Window& window, Editor& editor)
: r_window(window)
, r_editor(editor)
{
    std::printf("Interface\n");

    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui::GetStyle().WindowPadding = {0.0f, 0.0f};
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

    r_editor.render();

    render_draw_data();
}


static void
new_frame() noexcept
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();
}

static void
render_draw_data() noexcept
{
    ImGui::EndFrame();
    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
