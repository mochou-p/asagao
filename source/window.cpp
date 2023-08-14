// asagao/source/window.cpp


#include "window.hpp"

#define WINDOW_TITLE "Asagao"
#define WINDOW_ICON_PATH "resources\\icons\\logo.png"
#define WINDOW_VSYNC 1

Window::Window()
{
    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_handle = glfwCreateWindow(1, 1, WINDOW_TITLE, nullptr, nullptr);

    if (!m_handle)
        exit(EXIT_FAILURE);

    glfwMaximizeWindow(m_handle);
    glfwMakeContextCurrent(m_handle);
    glfwSwapInterval(WINDOW_VSYNC);

    m_interface = new Gui(m_handle);

    run();
}

Window::~Window()
{
    delete m_interface;

    glfwTerminate();
}

void Window::run()
{
    while (!glfwWindowShouldClose(m_handle))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);

        m_interface->draw();

        glfwSwapBuffers(m_handle);
    }
}
