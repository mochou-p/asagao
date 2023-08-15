// asagao/source/app.cpp


#include "app.hpp"

App::App(const char* t_name)
{
    m_window    = new Window(t_name);
    m_interface = new Gui(m_window->m_handle);
}

App::~App()
{
    delete m_interface;
    delete m_window;
}

void App::run()
{
    while (m_window->is_open())
    {
        m_interface->draw();
        m_window->swap_buffers();
    }
}
