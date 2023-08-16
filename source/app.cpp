// asagao/source/app.cpp


#include <cmath>
#include "app.hpp"

App::App(const char* t_name)
{
    m_win = std::make_unique<Window>(t_name);
    m_gui = std::make_unique<Gui>(m_win->m_handle);
}

void App::run()
{
    double time;

    while (m_win->is_open())
    {
        time = glfwGetTime();
        glClearColor(1.0f, sinf(time), -sinf(time), 1.0f);

        m_gui->draw();
        m_win->swap_buffers();
    }
}
