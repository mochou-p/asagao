// asagao/includes/window.hpp


#pragma once


#include "renderer.hpp"
#include "interface.hpp"

#include <string>


class Window
{
public:
    Window(const std::string& window_title, const unsigned short window_width, const unsigned short window_height);
    ~Window();

private:
    Renderer  m_renderer;
    Interface m_interface;
};
