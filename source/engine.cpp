// asagao/source/engine.cpp


#include "engine.hpp"

#include <cstdio>


Engine::Engine
(const std::string& window_title, const unsigned short window_width, const unsigned short window_height)
: m_window(window_title, window_width, window_height, m_editor)
, m_editor(m_window)
{
    std::printf("Engine\n");

    m_window.init();
}

Engine::~Engine()
{
    std::printf("~Engine\n");
}

void
Engine::start() const
{
    while (m_window.is_open())
    {
        m_window.poll_events();
        m_window.clear();

        m_window.render_ui();

        m_window.swap_buffers();
    }
}
