// asagao/source/interface.cpp


#include "interface.hpp"

#include "window.hpp"

#include <cstdio>


Interface::Interface
(Window& window)
: r_window(window)
{
    std::printf("Interface (window = %s)\n", window.get_title().c_str());
}

Interface::~Interface()
{
    std::printf("~Interface\n");
}
