// asagao/includes/window.hpp


#pragma once
#ifndef __window_hpp_
#define __window_hpp_

#define GLFW_INCLUDE_NONE
#include "glfw3.h"
#include "glm.hpp"

class Window
{
public:
    Window(const std::string& title, int width, int height);
    ~Window();

    bool is_open()      const;
    void poll_events()  const;
    void swap_buffers() const;

    static inline GLFWwindow* handle;
    static inline glm::vec2   size;
    static inline glm::vec2   mouse_pos;
    static inline bool        was_resized;
    static inline bool        moving_view;
private:
    void init(const std::string& title, int width, int height);
};

#endif  // __window_hpp_
