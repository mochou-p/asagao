// asagao/source/window.cpp


#include "asagao.hpp"

#include "image.hpp"
#include "log.hpp"
#include "style.hpp"


#define OPENGL_VER_MAJOR 4
#define OPENGL_VER_MINOR 6
#define VSYNC            1
#define ICON_COUNT       5
#define WINDOW_ICON_PATH "branding/"


static void framebuffer_size_callback(GLFWwindow* window, i32 width,   i32 height);
static void           scroll_callback(GLFWwindow* window, f64 xoffset, f64 yoffset);
static void     mouse_button_callback(GLFWwindow* window, i32 button,  i32 action, i32 mods);
static void  cursor_position_callback(GLFWwindow* window, f64 xpos,    f64 ypos);


namespace Asagao
{
    Window::Window
    (const str& title, u16 width, u16 height)
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

    f64
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
    (const str& title, u16 width, u16 height)
    {
        if (handle)
            LOG_FATAL("only one instance of window is allowed");

        assert(glfwInit());

        LOG_INFO(str("GLFW ") + glfwGetVersionString());

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VER_MAJOR);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VER_MINOR);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

        assert(handle);

        Image images[ICON_COUNT]
        {
            {WINDOW_ICON_PATH + str("asagao-256x256.png")},
            {WINDOW_ICON_PATH + str("asagao-128x128.png")},
            {WINDOW_ICON_PATH + str("asagao-64x64.png")},
            {WINDOW_ICON_PATH + str("asagao-32x32.png")},
            {WINDOW_ICON_PATH + str("asagao-16x16.png")}
        };

        GLFWimage icons[ICON_COUNT];
        
        for (u8 i = 0; i < ICON_COUNT; ++i)
        {
            icons[i].width  = images[i].get_width();
            icons[i].height = images[i].get_height();
            icons[i].pixels = images[i].get_data();
        }

        glfwSetWindowIcon(handle, ICON_COUNT, icons);

        if (const GLFWvidmode* screen = glfwGetVideoMode(glfwGetPrimaryMonitor()))
        {
            u16 x = (screen->width  - width)  * 0.5f;
            u16 y = (screen->height - height) * 0.5f;

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
        v2 top_left      = size * Layout::scene.pos;
        v2 bottom_right  = size;
        bottom_right    *= Layout::scene.pos + Layout::scene.size;

        return
        (
            top_left.x < mouse_pos.x
            && mouse_pos.x < bottom_right.x
            &&  top_left.y <    mouse_pos.y
            && mouse_pos.y < bottom_right.y
        );
    }
}  // Asagao::


static void
framebuffer_size_callback
(GLFWwindow* window, i32 width, i32 height)
{
    Asagao::Window.size = {width, height};

    v2 pos  = {Asagao::Window.size * Layout::scene.pos };
    v2 size = {Asagao::Window.size * Layout::scene.size};

    glViewport(pos.x, pos.y, size.x, size.y);

    Asagao::Camera.update_projection();
}

static inline bool sign(f32 value) { return value >= 0.0f; }

static void
scroll_callback
(GLFWwindow* window, f64 xoffset, f64 yoffset)
{
    if (!yoffset || Asagao::Interface.get_view() != SCENE_VIEW || !Asagao::Window.mouse_hovers_scene())
        return;

    v2 mouse_pos_frac  = Asagao::Window.mouse_pos / Asagao::Window.size;
    mouse_pos_frac    *= -2;
    mouse_pos_frac    +=  1;
    mouse_pos_frac    /= Layout::scene.size;
    mouse_pos_frac.y  *= -1;
    mouse_pos_frac    *= yoffset / abs(yoffset);

    v2 offset  = mouse_pos_frac;
    offset    *= Asagao::Window.size;
    offset    *= Asagao::Renderer.zoom;
    offset    *= 0.05f;

    Asagao::Camera.move({offset.x, offset.y, 0.0f});

    Asagao::Renderer.zoom += Asagao::Renderer.zoom / (sign(yoffset) ? -20 : 19);

    Asagao::Camera.update_projection();
}

static void
mouse_button_callback
(GLFWwindow* window, i32 button, i32 action, i32 mods)
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
}

static void
cursor_position_callback
(GLFWwindow* window, f64 xpos, f64 ypos)
{
    if (Asagao::Interface.get_view() != SCENE_VIEW)
        return;

    if (Asagao::Window.moving_view)
    {
        v2 diff = {(Asagao::Window.mouse_pos - v2(xpos, ypos))
            * (Asagao::Renderer.zoom * 2)};

        Asagao::Camera.move({-diff.x, diff.y, 0.0f});
    }

    Asagao::Window.mouse_pos = {xpos, ypos};
}
