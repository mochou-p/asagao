// asagao/source/window.cpp


#include "window.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#define VSYNC 1

Window::Window(std::string t_title, const int t_width, const int t_height)
{
    if (!glfwInit())
        exit(EXIT_FAILURE);

    m_handle = glfwCreateWindow(t_width, t_height, t_title.c_str(), nullptr, nullptr);

    if (!m_handle)
        exit(EXIT_FAILURE);

    glfwMakeContextCurrent(m_handle);
    glfwSwapInterval(VSYNC);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_handle, true);
    ImGui_ImplOpenGL3_Init();
}

Window::~Window()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
}

void Window::run()
{
    while (!glfwWindowShouldClose(m_handle))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("hi", nullptr);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_handle);
    }
}
