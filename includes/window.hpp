// asagao/includes/window.hpp


#pragma once
#ifndef __window_hpp_
#define __window_hpp_

#include <string>
#define GLFW_INCLUDE_NONE
#include "glfw3.h"
#include "glm.hpp"
#include "style.hpp"

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
    static inline bool        moving_view;
private:
    void init(const std::string& title, int width, int height);
};

inline bool mouse_hovers_scene()
{
    glm::vec2 top_left      = Window::size * Layout::scene.pos;
    glm::vec2 bottom_right  = Window::size;
    bottom_right           *= Layout::scene.pos + Layout::scene.size;

    return
    (
        top_left.x < Window::mouse_pos.x &&
        Window::mouse_pos.x < bottom_right.x &&
        top_left.y < Window::mouse_pos.y &&
        Window::mouse_pos.y < bottom_right.y
    );
}

#endif  // __window_hpp_
