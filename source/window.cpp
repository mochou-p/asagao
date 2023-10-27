// asagao/source/window.cpp


#include "window.hpp"

#include <cstdio>
#include <stdexcept>


#define OPENGL_VERSION_MAJOR 4
#define OPENGL_VERSION_MINOR 6
#define VSYNC                1


Window::Window
(const std::string& title, const unsigned short width, const unsigned short height)
:     m_title(title)
,     m_width(width)
,    m_height(height)
, m_interface(*this)
{
    if (!glfwInit())
        throw std::runtime_error("failed to initialise GLFW");

    std::printf("Window (%s, %hu, %hu)\n", m_title.c_str(), m_width, m_height);
}

Window::~Window()
{
    glfwDestroyWindow(m_handle);
    glfwTerminate();

    std::printf("~Window\n");
}

void
Window::init()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE,        GLFW_OPENGL_CORE_PROFILE);

    m_handle = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);

    if (!m_handle)
    {
        glfwTerminate();
        throw std::runtime_error("failed to create a GLFW window");
    }

    if (auto screen = glfwGetVideoMode(glfwGetPrimaryMonitor()))
    {
        unsigned short x = (screen->width  - m_width)  * 0.5f;
        unsigned short y = (screen->height - m_height) * 0.5f;

        glfwSetWindowPos(m_handle, x, y);
    }

    glfwMakeContextCurrent(m_handle);
    glfwSwapInterval(VSYNC);
}
