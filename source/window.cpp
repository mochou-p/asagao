// asagao/source/window.cpp


#include <iostream>

#include "window.hpp"

#define VSYNC 1

Window::Window(const char* t_title)
{
    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_handle = glfwCreateWindow(1, 1, t_title, nullptr, nullptr);

    if (!m_handle)
        exit(EXIT_FAILURE);

    glfwMaximizeWindow(m_handle);
    glfwMakeContextCurrent(m_handle);
    glfwSwapInterval(VSYNC);

    std::cout << "OpenGL\t" << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLFW\t"   << glfwGetVersionString()  << std::endl;
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
    glClear(GL_COLOR_BUFFER_BIT);

    return true;
}

void Window::swap_buffers()
{
    glfwSwapBuffers(m_handle);
}
