// asagao/includes/window.hpp


#pragma once

#include "gui.hpp"

class Window
{
public:
    Window();
    ~Window();

    void run();
private:
    GLFWwindow* m_handle;
    Gui*        m_interface;
};
