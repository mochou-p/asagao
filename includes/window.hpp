// asagao/includes/window.hpp


#pragma once

#define APP_TITLE "Asagao"
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

namespace Asagao
{
    class Window
    {
    public:
        static Window& get_instance()
        {
            static Window instance(APP_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);

            return instance;
        }
    private:
        Window(const str& title, u16 width, u16 height);
        ~Window();

        Window           (const Window&) = delete;
        Window& operator=(const Window&) = delete;


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
