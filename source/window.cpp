// asagao/source/window.cpp


#include "window.hpp"

#include <cstdio>
#include <stdexcept>


#define OPENGL_VERSION_MAJOR 4
#define OPENGL_VERSION_MINOR 6
#define VSYNC                1


static void window_size_callback(GLFWwindow* handle, int width, int height);


Window::Window
(const std::string& title, const unsigned short width, const unsigned short height, Editor& editor)
:     m_title(title)
,     m_width(width)
,    m_height(height)
, m_interface(*this, editor)
{
    std::printf("Window\n");

    if (!glfwInit())
        throw std::runtime_error("failed to initialise GLFW");
}

Window::~Window()
{
    std::printf("~Window\n");

    glfwDestroyWindow(m_handle);
    glfwTerminate();
}


void
Window::init()
{
    create_main_window();

    m_interface.init();
}

void
Window::create_main_window()
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
        const int x = (screen->width  - m_width)  * 0.5f;
        const int y = (screen->height - m_height) * 0.5f;

        glfwSetWindowPos(m_handle, x, y);
    }

    glfwSetWindowUserPointer(m_handle, this);

    glfwSetWindowSizeCallback(m_handle, window_size_callback);

    glfwMakeContextCurrent(m_handle);
    glfwSwapInterval(VSYNC);
}


static void
window_size_callback
(GLFWwindow* handle, int width, int height)
{
    auto window = static_cast<Window*>(glfwGetWindowUserPointer(handle));

    window->set_width(width);
    window->set_height(height);

    window->clear();
    window->render_ui();
    window->swap_buffers();
}
