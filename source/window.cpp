// asagao/source/window.cpp


#include "window.hpp"

#include <cstdio>


Window::Window
(const std::string& window_title, const unsigned short window_width, const unsigned short window_height)
{
    std::printf("Window (%s, %hu, %hu)\n", window_title.c_str(), window_width, window_height);
}

Window::~Window()
{
    std::printf("~Window\n");
}
