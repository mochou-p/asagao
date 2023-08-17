// asagao/source/window.cpp


#include <iostream>
#include "window.hpp"
#include "glad/glad.h"

#define VSYNC 1

void framebuffer_size_callback
([[maybe_unused]] GLFWwindow* t_window, int t_width, int t_height)
{
    glViewport(0, 0, t_width, t_height);
}

void load_opengl_functions()
{
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cerr << "gladLoadGLLoader failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "OpenGL\t" << glGetString(GL_VERSION) << std::endl;
}

Window::Window(const char* t_title)
{
    if (!glfwInit())
    {
        std::cerr << "glfwInit failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "GLFW\t" << glfwGetVersionString() << std::endl;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_handle = glfwCreateWindow(1600, 900, t_title, nullptr, nullptr);

    if (!m_handle)
    {
        std::cerr << "glfwCreateWindow failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwSetFramebufferSizeCallback(m_handle, framebuffer_size_callback);

    glfwMakeContextCurrent(m_handle);
    glfwSwapInterval(VSYNC);

    load_opengl_functions();
}

Window::~Window()
{
    glfwTerminate();
}

bool Window::is_open()
{
    if (glfwWindowShouldClose(m_handle))
        return false;

    glfwPollEvents();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    return true;
}

void Window::swap_buffers()
{
    glfwSwapBuffers(m_handle);
}
