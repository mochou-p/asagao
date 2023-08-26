// asagao/source/window.cpp


#include <iostream>
#include "window.hpp"
#include "style.hpp"
#include "utils.hpp"
#include "renderer.hpp"
#include "application.hpp"

#define VSYNC 1
#define OPENGL_VER_MAJOR 4
#define OPENGL_VER_MINOR 6

static void
framebuffer_size_callback([[maybe_unused]] GLFWwindow* window,
                                           int         width,
                                           int         height)
{
    Window::size = {width, height};

    glm::vec2 pos  = {Window::size * Layout::scene.pos };
    glm::vec2 size = {Window::size * Layout::scene.size};

    glViewport(pos.x, pos.y, size.x, size.y);

    Application::aspect = Window::size * Layout::scene.size * Renderer::zoom;
    Application::view_changed = true;
}

static void
scroll_callback([[maybe_unused]] GLFWwindow* window,
                [[maybe_unused]] double      xoffset,
                                 double      yoffset)
{
    if (!yoffset) return;

    // to always zoom by 5% of zoom    vvvvv
    Renderer::zoom -= Renderer::zoom * 0.05f * yoffset;
    Application::aspect = Window::size * Layout::scene.size * Renderer::zoom;
    Application::view_changed = true;
}

static void
mouse_button_callback([[maybe_unused]] GLFWwindow* window,
                                       int         button,
                                       int         action,
                      [[maybe_unused]] int         mods)
{
    if (button != GLFW_MOUSE_BUTTON_LEFT) return;

    if (!action)
    {
        Window::moving_view = false;
        return;
    }

    glm::vec2 top_left     = Window::size * Layout::scene.pos;
    glm::vec2 bottom_right = Window::size
        * (Layout::scene.pos + Layout::scene.size);

    if
    (
        top_left.x < Window::mouse_pos.x &&
        Window::mouse_pos.x < bottom_right.x &&
        top_left.y < Window::mouse_pos.y &&
        Window::mouse_pos.y < bottom_right.y
    )
    { Window::moving_view = true; }
}

static void
cursor_position_callback([[maybe_unused]] GLFWwindow* window,
                                          double      xpos,
                                          double      ypos)
{
    if (Window::moving_view)
    {
        glm::vec2 diff = {(Window::mouse_pos - glm::vec2(xpos, ypos))
            * (Renderer::zoom * 2)};
        Application::camera += glm::vec2(diff.x, -diff.y);

        Application::view_changed = true;
    }

    Window::mouse_pos = {xpos, ypos};
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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VER_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VER_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    handle = glfwCreateWindow(width, height, title.c_str(), nullptr,
        nullptr);

    if (!handle) quit("glfwCreateWindow failed");

    const GLFWvidmode* screen = glfwGetVideoMode(glfwGetPrimaryMonitor());

    if (!screen) quit("glfwGetVideoMode failed");

    int x = (screen->width  - width)  * 0.5f;
    int y = (screen->height - height) * 0.5f;

    glfwSetWindowPos(handle, x, y);

    glfwSetFramebufferSizeCallback(handle, framebuffer_size_callback);
    glfwSetScrollCallback(         handle,           scroll_callback);
    glfwSetMouseButtonCallback(    handle,     mouse_button_callback);
    glfwSetCursorPosCallback(      handle,  cursor_position_callback);

    glfwMakeContextCurrent(handle);
    glfwSwapInterval(VSYNC);
}
