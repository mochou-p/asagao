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
    Window::was_resized = true;

    Window::size = {width, height};

    glm::vec2 pos  {Window::size * Layout::scene.pos };
    glm::vec2 size {Window::size * Layout::scene.size};

    glViewport(pos.x, pos.y, size.x, size.y);
}

static void
scroll_callback([[maybe_unused]] GLFWwindow* window,
                [[maybe_unused]] double      xoffset,
                                 double      yoffset)
{
    if (!yoffset) return;

    Renderer::was_resized = true;

    Renderer::zoom -= Renderer::zoom * 0.05f * yoffset;
}

static void
key_callback([[maybe_unused]] GLFWwindow* window,
                              int         key,
             [[maybe_unused]] int         scancode,
                              int         action,
             [[maybe_unused]] int         mods)
{
    if (action == GLFW_REPEAT) return;

    switch (key)
    {
        case GLFW_KEY_W:
        case GLFW_KEY_UP:
            Application::moving.y += 1 == action ? 1 : -1;
            break;
        case GLFW_KEY_A:
        case GLFW_KEY_LEFT:
            Application::moving.x += 0 == action ? 1 : -1;
            break;
        case GLFW_KEY_S:
        case GLFW_KEY_DOWN:
            Application::moving.y += 0 == action ? 1 : -1;
            break;
        case GLFW_KEY_D:
        case GLFW_KEY_RIGHT:
            Application::moving.x += 1 == action ? 1 : -1;
            break;
        default:
            break;
    }
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
    glfwSetScrollCallback(         handle,           scroll_callback);
    glfwSetKeyCallback(            handle,              key_callback);

    const GLFWvidmode* screen = glfwGetVideoMode(glfwGetPrimaryMonitor());

    if (!screen) quit("glfwGetVideoMode failed");

    int x = (screen->width  - width)  * 0.5f;
    int y = (screen->height - height) * 0.5f;

    glfwSetWindowPos(handle, x, y);

    glfwMakeContextCurrent(handle);
    glfwSwapInterval(VSYNC);
}
