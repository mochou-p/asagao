// asagao/includes/window.hpp


#pragma once

#include <string>

#include "gui.hpp"

class Window
{
public:
    Window(std::string, const int, const int);
    ~Window();

    void run();
private:
    GLFWwindow* m_handle;
    Gui*        m_interface;
};
