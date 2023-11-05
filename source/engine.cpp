// asagao/source/engine.cpp


#include "engine.hpp"

#include <cstdio>


Engine::Engine
(const std::string& window_title, const unsigned short window_width, const unsigned short window_height)
: m_window(window_title, window_width, window_height, m_editor)
, m_editor(m_window, m_scene)
{
    std::printf("Engine\n");

    m_scene = std::make_unique<Scene>();
    m_scene->new_object(std::make_unique<GameObject>("Player"));
    m_scene->new_object(std::make_unique<TileMap>("Level 1"));
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
