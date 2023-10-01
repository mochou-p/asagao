// asagao/includes/window.hpp


#pragma once


#include "singleton.hpp"


#define APP_TITLE     "Asagao"
#define WINDOW_WIDTH  1600
#define WINDOW_HEIGHT 900


namespace Asagao
{
    class Window
    {
    SINGLETON_CD(Window)

    public:
        bool is_open()            const;
        void poll_events()        const;
        void swap_buffers()       const;
        bool mouse_hovers_scene() const;
        f64  get_time()           const;
        void resize();

        GLFWwindow* handle;
        v2          size;
        v2          mouse_pos;
        bool        moving_view;
    private:
        void init(const str& title, u16 width, u16 height);
    };
}  // Asagao::
