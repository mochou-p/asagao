// asagao/source/window.cpp


#include <iostream>
#include "window.hpp"
#include "style.hpp"
#include "utils.hpp"
#include "renderer.hpp"

#define VSYNC 1
#define OPENGL_VER_MAJOR 4
#define OPENGL_VER_MINOR 6

static void
framebuffer_size_callback([[maybe_unused]] GLFWwindow* window,
                                           int         width,
                                           int         height)
{
    Window::width  = width;
    Window::height = height;
    Window::was_resized = true;

    glViewport(width * Layout::scene.pos.x, height * Layout::scene.pos.y,
        width * Layout::scene.size.x, height * Layout::scene.size.y);
}

Window::Window(const std::string& title,
                     int          width,
                     int          height)
{
    init(title, width, height);
    Renderer::init();
    framebuffer_size_callback(handle, width, height);
}

Window::~Window()
{
    glfwTerminate();
}

bool
Window::is_open() const
{
    return !glfwWindowShouldClose(handle);
}

void
Window::poll_events() const
{
    glfwPollEvents();
}

void
Window::swap_buffers() const
{
    glfwSwapBuffers(handle);
}

void
Window::init(const std::string& title,
                   int          width,
                   int          height)
{
    if (handle)      quit("only one instance of window is allowed");
    if (!glfwInit()) quit("glfwInit failed");

    std::cout << "GLFW\t" << glfwGetVersionString() << std::endl;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VER_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VER_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    handle = glfwCreateWindow(width, height, title.c_str(), nullptr,
        nullptr);

    if (!handle) quit("glfwCreateWindow failed");

    glfwSetFramebufferSizeCallback(handle, framebuffer_size_callback);

    const GLFWvidmode* screen = glfwGetVideoMode(glfwGetPrimaryMonitor());

    if (!screen) quit("glfwGetVideoMode failed");

    int x = (screen->width  - width)  * 0.5f;
    int y = (screen->height - height) * 0.5f;

    glfwSetWindowPos(handle, x, y);

    glfwMakeContextCurrent(handle);
    glfwSwapInterval(VSYNC);
}
