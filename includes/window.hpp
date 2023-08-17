// asagao/includes/window.hpp


#pragma once

#define GLFW_INCLUDE_NONE
#include "glfw3.h"

class Window
{
public:
    Window(const char*);
    ~Window();

    bool is_open();
    void swap_buffers();

    GLFWwindow* m_handle;
};
