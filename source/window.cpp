// asagao/source/window.cpp


#include <cassert>
#include <array>
#include "window.hpp"
#include "style.hpp"
#include "renderer.hpp"
#include "application.hpp"
#include "log.hpp"
#include "image.hpp"

#define VSYNC 1
#define OPENGL_VER_MAJOR 4
#define OPENGL_VER_MINOR 6
#define WINDOW_ICON_PATH "resources/branding/"

static void
framebuffer_size_callback
(
 GLFWwindow* window,
 int         width,
 int         height
)
{
    Window::size = {width, height};

    glm::vec2 pos  = {Window::size * Layout::scene.pos };
    glm::vec2 size = {Window::size * Layout::scene.size};

    glViewport(pos.x, pos.y, size.x, size.y);

    Application::camera.update_projection();

    (void)(window);
}

static bool
mouse_hovers_screen()
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

static void
scroll_callback
(
 GLFWwindow* window,
 double      xoffset,
 double      yoffset
)
{
    if (!yoffset || !mouse_hovers_screen()) return;

    glm::vec2 mouse_pos_frac = Window::mouse_pos / Window::size;
    mouse_pos_frac   *= -2;
    mouse_pos_frac   +=  1;
    mouse_pos_frac   /= Layout::scene.size;
    mouse_pos_frac.y *= -1;
    mouse_pos_frac   *= yoffset / abs(yoffset);

    glm::vec2 offset = mouse_pos_frac * Window::size * Renderer::zoom
        * 0.05f;


    Renderer::zoom -= Renderer::zoom * 0.05f * yoffset;

    Application::camera.move({offset.x, offset.y, 0.0f});
    Application::camera.update_projection();

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
    if (button != GLFW_MOUSE_BUTTON_LEFT) return;

    if (!action)
    {
        Window::moving_view = false;
        return;
    }

    if (mouse_hovers_screen())
        Window::moving_view = true;

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
    if (Window::moving_view)
    {
        glm::vec2 diff = {(Window::mouse_pos - glm::vec2(xpos, ypos))
            * (Renderer::zoom * 2)};

        Application::camera.move({-diff.x, diff.y, 0.0f});
    }

    Window::mouse_pos = {xpos, ypos};

    (void)(window);
}

Window::Window
(
 const std::string& title,
       int          width,
       int          height
)
{
    init(title, width, height);
    Renderer::init();
    framebuffer_size_callback(handle, width, height);
}

Window::~Window()
{
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

    std::array<Image, 5> images
    {
        Image(WINDOW_ICON_PATH + std::string("asagao-256x256.png")),
        Image(WINDOW_ICON_PATH + std::string("asagao-128x128.png")),
        Image(WINDOW_ICON_PATH + std::string("asagao-64x64.png")),
        Image(WINDOW_ICON_PATH + std::string("asagao-32x32.png")),
        Image(WINDOW_ICON_PATH + std::string("asagao-16x16.png"))
    };

    GLFWimage icons[images.size()];
    
    for (unsigned char i = 0; i < images.size(); ++i)
    {
        icons[i].width  = images[i].get_width();
        icons[i].height = images[i].get_height();
        icons[i].pixels = images[i].get_data();
    }

    glfwSetWindowIcon(handle, images.size(), icons);

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
}
