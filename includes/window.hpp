// asagao/includes/window.hpp


#pragma once
#ifndef __window_hpp_
#define __window_hpp_

#define GLFW_INCLUDE_NONE
#include "glfw3.h"
#include "glad/glad.h"

class Window
{
public:
    Window(const std::string&, int, int);
    ~Window() { glfwTerminate(); }

    bool is_open()      { return !glfwWindowShouldClose(handle); }
    void events()       { glfwPollEvents();                      }
    void clear()        { glClear(GL_COLOR_BUFFER_BIT);          }
    void swap_buffers() { glfwSwapBuffers(handle);               }

    static inline GLFWwindow* handle;
    static inline int         width;
    static inline int         height;
private:
    void init(const std::string&, int, int);
};

#endif  // __window_hpp_
