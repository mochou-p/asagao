// asagao/includes/window.hpp


#pragma once


#include "renderer.hpp"
#include "interface.hpp"

#include "glfw3.h"

#include <string>


class Window
{
public:
    Window(const std::string& title, const unsigned short width, const unsigned short height);
    ~Window();

    void init();

    [[nodiscard]] inline auto is_open()      const noexcept { return !glfwWindowShouldClose(m_handle); }
                  inline auto poll_events()  const noexcept { glfwPollEvents();                        }
                  inline auto clear()        const noexcept { glClear(GL_COLOR_BUFFER_BIT);            }
                  inline auto swap_buffers() const noexcept { glfwSwapBuffers(m_handle);               }
                  inline auto render_ui()    const noexcept { m_interface.render();                    }

    [[nodiscard]] inline auto get_handle()   const noexcept { return m_handle; }
    [[nodiscard]] inline auto get_title()    const noexcept { return m_title;  }

private:
    void create_main_window();

    std::string    m_title;
    unsigned short m_width;
    unsigned short m_height;

    GLFWwindow*    m_handle;

    Renderer       m_renderer;
    Interface      m_interface;
};
