// asagao/source/window.cpp


#include "asagao.hpp"

#include "image.hpp"
#include "log.hpp"
#include "style.hpp"

#define GLFW_INCLUDE_NONE
#include "glfw3.h"
#include "glad.h"

#define VSYNC 1
#define OPENGL_VER_MAJOR 4
#define OPENGL_VER_MINOR 6
#define WINDOW_ICON_PATH "resources/branding/"
#define ICON_COUNT 5

static void
framebuffer_size_callback
(
 GLFWwindow* window,
 int         width,
 int         height
)
{
    Asagao::Window.size = {width, height};

    glm::vec2 pos  = {Asagao::Window.size * Layout::scene.pos };
    glm::vec2 size = {Asagao::Window.size * Layout::scene.size};

    glViewport(pos.x, pos.y, size.x, size.y);

    Asagao::Camera.update_projection();

    (void)(window);
}

static inline bool sign(float value) { return value >= 0.0f; }

static void
scroll_callback
(
 GLFWwindow* window,
 double      xoffset,
 double      yoffset
)
{
    if (!yoffset || Asagao::Interface.get_view() != SCENE_VIEW || !Asagao::Window.mouse_hovers_scene())
        return;

    glm::vec2 mouse_pos_frac  = Asagao::Window.mouse_pos / Asagao::Window.size;
    mouse_pos_frac           *= -2;
    mouse_pos_frac           +=  1;
    mouse_pos_frac           /= Layout::scene.size;
    mouse_pos_frac.y         *= -1;
    mouse_pos_frac           *= yoffset / abs(yoffset);

    glm::vec2 offset  = mouse_pos_frac;
    offset           *= Asagao::Window.size;
    offset           *= Asagao::Renderer.zoom;
    offset           *= 0.05f;

    Asagao::Camera.move({offset.x, offset.y, 0.0f});

    Asagao::Renderer.zoom += Asagao::Renderer.zoom / (sign(yoffset) ? -20 : 19);

    Asagao::Camera.update_projection();

    (void)(window);
    (void)(xoffset);
}

static void
mouse_button_callback
(
 GLFWwindow* window,
 int         button,
 int         action,
 int         mods
)
{
    if (button != GLFW_MOUSE_BUTTON_LEFT || Asagao::Interface.get_view() != SCENE_VIEW)
        return;

    if (!action)
    {
        Asagao::Window.moving_view = false;
        return;
    }

    if (Asagao::Window.mouse_hovers_scene())
        Asagao::Window.moving_view = true;

    (void)(window);
    (void)(mods);
}

static void
cursor_position_callback
(
 GLFWwindow* window,
 double      xpos,
 double      ypos
)
{
    if (Asagao::Interface.get_view() != SCENE_VIEW)
        return;

    if (Asagao::Window.moving_view)
    {
        glm::vec2 diff = {(Asagao::Window.mouse_pos - glm::vec2(xpos, ypos))
            * (Asagao::Renderer.zoom * 2)};

        Asagao::Camera.move({-diff.x, diff.y, 0.0f});
    }

    Asagao::Window.mouse_pos = {xpos, ypos};

    (void)(window);
}

namespace Asagao
{
    Window::Window
    (
    const std::string& title,
        int            width,
        int            height
    )
    {
        init(title, width, height);
        Renderer.init();
    }

    Window::~Window()
    {
        glfwDestroyWindow(handle);

        glfwTerminate();
    }

    bool
    Window::is_open() const
    {
        return !glfwWindowShouldClose(handle);
    }

    void
    Window::poll_events() const
    {
        glfwPollEvents();
    }

    void
    Window::swap_buffers() const
    {
        glfwSwapBuffers(handle);
    }

    double
    Window::get_time() const
    {
        return glfwGetTime();
    }

    void
    Window::resize()
    {
        framebuffer_size_callback(handle, size.x, size.y);
    }

    void
    Window::init
    (
    const std::string& title,
        int          width,
        int          height
    )
    {
        if (handle)
            LOG_FATAL("only one instance of window is allowed");

        assert(glfwInit());

        LOG_INFO(std::string("GLFW ") + glfwGetVersionString());

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VER_MAJOR);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VER_MINOR);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        handle = glfwCreateWindow(width, height, title.c_str(), nullptr,
            nullptr);

        assert(handle);

        Image images[ICON_COUNT]
        {
            {WINDOW_ICON_PATH + std::string("asagao-256x256.png")},
            {WINDOW_ICON_PATH + std::string("asagao-128x128.png")},
            {WINDOW_ICON_PATH + std::string("asagao-64x64.png")},
            {WINDOW_ICON_PATH + std::string("asagao-32x32.png")},
            {WINDOW_ICON_PATH + std::string("asagao-16x16.png")}
        };

        GLFWimage icons[ICON_COUNT];
        
        for (unsigned char i = 0; i < ICON_COUNT; ++i)
        {
            icons[i].width  = images[i].get_width();
            icons[i].height = images[i].get_height();
            icons[i].pixels = images[i].get_data();
        }

        glfwSetWindowIcon(handle, ICON_COUNT, icons);

        if (const GLFWvidmode* screen = glfwGetVideoMode(glfwGetPrimaryMonitor()))
        {
            int x = (screen->width  - width)  * 0.5f;
            int y = (screen->height - height) * 0.5f;

            glfwSetWindowPos(handle, x, y);
        }

        glfwSetFramebufferSizeCallback (handle, framebuffer_size_callback);
        glfwSetScrollCallback          (handle,           scroll_callback);
        glfwSetMouseButtonCallback     (handle,     mouse_button_callback);
        glfwSetCursorPosCallback       (handle,  cursor_position_callback);

        glfwMakeContextCurrent(handle);
        glfwSwapInterval(VSYNC);

        size = {width, height};
    }

    bool
    Window::mouse_hovers_scene() const
    {
        glm::vec2 top_left      = size * Layout::scene.pos;
        glm::vec2 bottom_right  = size;
        bottom_right           *= Layout::scene.pos + Layout::scene.size;

        return
        (
            top_left.x < mouse_pos.x &&
            mouse_pos.x < bottom_right.x &&
            top_left.y < mouse_pos.y &&
            mouse_pos.y < bottom_right.y
        );
    }
}  // Asagao::
