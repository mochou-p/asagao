// asagao/source/window.cpp


#include <iostream>
#include "window.hpp"
#include "style.hpp"
#include "utils.hpp"

#define VSYNC 1
#define OPENGL_VER_MAJOR 4
#define OPENGL_VER_MINOR 6

static void framebuffer_size_callback
([[maybe_unused]] GLFWwindow* t_window, int t_width, int t_height)
{
    Window::width  = t_width;
    Window::height = t_height;

    glViewport(t_width * Layout::scene.pos.x, t_height * Layout::scene.pos.y,
        t_width * Layout::scene.size.x, t_height * Layout::scene.size.y);
}

static void load_opengl_functions()
{
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        quit("gladLoadGLLoader failed");

    std::cout << "OpenGL\t" << glGetString(GL_VERSION) << std::endl;
}

Window::Window(const std::string& t_title, int t_width, int t_height)
{
    init(t_title, t_width, t_height);
    load_opengl_functions();
    framebuffer_size_callback(handle, t_width, t_height);
}

void Window::init(const std::string& t_title, int t_width, int t_height)
{
    if (handle)      quit("only one instance of window is allowed");
    if (!glfwInit()) quit("glfwInit failed");

    std::cout << "GLFW\t" << glfwGetVersionString() << std::endl;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VER_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VER_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    handle = glfwCreateWindow(t_width, t_height, t_title.c_str(), nullptr,
        nullptr);

    if (!handle) quit("glfwCreateWindow failed");

    glfwSetFramebufferSizeCallback(handle, framebuffer_size_callback);

    const GLFWvidmode* screen = glfwGetVideoMode(glfwGetPrimaryMonitor());

    if (!screen) quit("glfwGetVideoMode failed");

    int x = (screen->width  - t_width)  * 0.5f;
    int y = (screen->height - t_height) * 0.5f;

    glfwSetWindowPos(handle, x, y);

    glfwMakeContextCurrent(handle);
    glfwSwapInterval(VSYNC);
}
