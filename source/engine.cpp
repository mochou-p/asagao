// asagao/source/engine.cpp


#include "engine.hpp"

#include <cstdio>


Engine::Engine
(const std::string& window_title, const unsigned short window_width, const unsigned short window_height)
: m_window(window_title, window_width, window_height)
{
    std::printf("Engine\n");
}

Engine::~Engine()
{
    std::printf("~Engine\n");
}
