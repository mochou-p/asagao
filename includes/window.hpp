// asagao/includes/window.hpp


#pragma once

#include <string>

#include "glfw3.h"

class Window
{
public:
    Window(std::string, const int, const int);
    ~Window();

    void run();
private:
    GLFWwindow* m_handle;
};
