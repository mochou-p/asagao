// asagao/source/app.cpp


#include "app.hpp"

App::App(const char* t_name)
{
    m_win = std::make_unique<Window>(t_name);
    m_gui = std::make_unique<Gui>(m_win->m_handle);
}

void App::run()
{
    while (m_win->is_open())
    {
        m_gui->draw();
        m_win->swap_buffers();
    }
}
