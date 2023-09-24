// asagao/includes/window.hpp


#pragma once

#include <string>
#define GLFW_INCLUDE_NONE
#include "glfw3.h"
#include "glm.hpp"
#include "style.hpp"

namespace Asagao
{
    class Window
    {
    public:
        static Window& get_instance()
        {
            static Window instance("Asagao", 1600, 900);

            return instance;
        }
    private:
        Window(const std::string& title, int width, int height);
        ~Window();

        Window           (const Window&) = delete;
        Window& operator=(const Window&) = delete;


    public:
        bool is_open()            const;
        void poll_events()        const;
        void swap_buffers()       const;
        bool mouse_hovers_scene() const;
        void resize();

        GLFWwindow* handle;
        glm::vec2   size;
        glm::vec2   mouse_pos;
        bool        moving_view;
    private:
        void init(const std::string& title, int width, int height);
    };
}  // Asagao::
