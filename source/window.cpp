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

Window::Window(const char* t_title, int t_width, int t_height)
{
    init(t_title, t_width, t_height);
    load_opengl_functions();
}

Window::~Window()
{
    glfwTerminate();
}

void Window::init(const char* t_title, int t_width, int t_height)
{
    if (handle)
    {
        std::cerr << "only one instance of window is allowed" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (!glfwInit())
    {
        std::cerr << "glfwInit failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "GLFW\t" << glfwGetVersionString() << std::endl;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    handle = glfwCreateWindow(t_width, t_height, t_title, nullptr, nullptr);

    if (!handle)
    {
        std::cerr << "glfwCreateWindow failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwSetFramebufferSizeCallback(handle, framebuffer_size_callback);

    const GLFWvidmode* screen = glfwGetVideoMode(glfwGetPrimaryMonitor());
    
    if (!screen)
    {
        std::cerr << "glfwGetVideoMode failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    int x = (screen->width  - t_width)  * 0.5f;
    int y = (screen->height - t_height) * 0.5f;

    glfwSetWindowPos(handle, x, y);

    glfwMakeContextCurrent(handle);
    glfwSwapInterval(VSYNC);
}

bool Window::is_open()
{
    if (glfwWindowShouldClose(handle))
        return false;

    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);

    return true;
}

void Window::swap_buffers()
{
    glfwSwapBuffers(handle);
}
