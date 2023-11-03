// asagao/includes/window.hpp


#pragma once


#include "renderer.hpp"
#include "interface.hpp"

#include <string>


class Window
{
public:
    Window(const std::string& title, const unsigned short width, const unsigned short height, Editor& editor);
    ~Window();

    void init();

    [[nodiscard]] inline auto is_open      () const noexcept -> bool           { return !glfwWindowShouldClose(m_handle); }
                  inline auto poll_events  () const noexcept -> void           { glfwPollEvents();                        }
                  inline auto clear        () const noexcept -> void           { m_renderer.clear();                      }
                  inline auto swap_buffers () const noexcept -> void           { glfwSwapBuffers(m_handle);               }
                  inline auto render_ui    () const noexcept -> void           { m_interface.render();                    }

    [[nodiscard]] inline auto get_handle   () const noexcept -> GLFWwindow*    { return m_handle;  }
    [[nodiscard]] inline auto get_title    () const noexcept -> std::string    { return m_title;   }
    [[nodiscard]] inline auto get_width    () const noexcept -> unsigned short { return m_width;   }
    [[nodiscard]] inline auto get_height   () const noexcept -> unsigned short { return m_height;  }

    inline auto set_width  (unsigned short value)   noexcept -> void           { m_width  = value; }
    inline auto set_height (unsigned short value)   noexcept -> void           { m_height = value; }

private:
    void create_main_window();

    std::string    m_title;
    unsigned short m_width;
    unsigned short m_height;

    GLFWwindow*    m_handle;

    Renderer       m_renderer;
    Interface      m_interface;
};
