// asagao/source/window.cpp


#include "window.hpp"

#include <cstdio>


Window::Window
(const std::string& title, const unsigned short width, const unsigned short height)
:     m_title(title)
,     m_width(width)
,    m_height(height)
, m_interface(*this)
{
    std::printf("Window (%s, %hu, %hu)\n", m_title.c_str(), m_width, m_height);
}

Window::~Window()
{
    std::printf("~Window\n");
}
