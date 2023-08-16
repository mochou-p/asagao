// asagao/includes/window.hpp


#pragma once

#include "glad/glad.h"
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
