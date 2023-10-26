// asagao/includes/window.hpp


#pragma once


#include "renderer.hpp"
#include "interface.hpp"

#include <string>


class Window
{
public:
    Window(const std::string& title, const unsigned short width, const unsigned short height);
    ~Window();

    Window(const Window&) = delete;

    std::string get_title() { return m_title; }

private:
    std::string    m_title;
    unsigned short m_width;
    unsigned short m_height;

    Renderer       m_renderer;
    Interface      m_interface;
};
