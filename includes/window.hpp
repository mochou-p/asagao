// asagao/includes/window.hpp


#pragma once

#define GLFW_INCLUDE_NONE
#include "glfw3.h"

class Window
{
public:
    Window(const char*, int, int);
    ~Window();

    bool is_open();
    void swap_buffers();

    static inline GLFWwindow* handle;
private:
    void init(const char*, int, int);
};
