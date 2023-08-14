// asagao/source/window.cpp


#include "window.hpp"

#define VSYNC 1

Window::Window(std::string t_title, const int t_width, const int t_height)
{
    if (!glfwInit())
        exit(EXIT_FAILURE);

    m_handle = glfwCreateWindow(t_width, t_height, t_title.c_str(), nullptr, nullptr);

    if (!m_handle)
        exit(EXIT_FAILURE);

    glfwMakeContextCurrent(m_handle);
    glfwSwapInterval(VSYNC);

    m_interface = new Gui(m_handle);
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
