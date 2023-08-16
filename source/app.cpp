// asagao/source/app.cpp


#include "app.hpp"

App::App(const char* t_name)
{
    m_window = std::make_unique<Window>(t_name);
    m_gui    = std::make_unique<Gui>(m_window->m_handle);
}

void App::run()
{
    while (m_window->is_open())
    {
        m_gui->draw();
        m_window->swap_buffers();
    }
}
