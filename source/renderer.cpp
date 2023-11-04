// asagao/source/renderer.cpp


#include "renderer.hpp"
#include "window.hpp"

#include <cstdio>
#include <stdexcept>


#define DEFAULT_SHADER "tile"
#define COLOR_RESET    "\33[0m"
#define COLOR_GREEN    "\33[32m"
#define COLOR_BLUE     "\33[34m"
#define COLOR_YELLOW   "\33[33m"
#define COLOR_RED      "\33[31m"


static void GLAPIENTRY debug_message_callback(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* message, const void* param) noexcept;


Renderer::Renderer
(Window& window)
: m_shader(DEFAULT_SHADER)
, r_window(window)
{
    r_window.init();

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        throw std::runtime_error("failed to load OpenGL functions");

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debug_message_callback, nullptr);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glActiveTexture(GL_TEXTURE0);

    std::printf("Renderer\n");
}

Renderer::~Renderer()
{
    std::printf("~Renderer\n");
}


static void GLAPIENTRY
debug_message_callback
(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* message, const void* param) noexcept
{
    static std::string text;

    switch (severity)
    {
    case GL_DEBUG_SEVERITY_NOTIFICATION: text += COLOR_GREEN  "[NOTIFICATION] " COLOR_RESET; break;
    case GL_DEBUG_SEVERITY_LOW:          text += COLOR_BLUE   "[LOW]          " COLOR_RESET; break;
    case GL_DEBUG_SEVERITY_MEDIUM:       text += COLOR_YELLOW "[MEDIUM]       " COLOR_RESET; break;
    case GL_DEBUG_SEVERITY_HIGH:         text += COLOR_RED    "[HIGH]         " COLOR_RESET; break;
    }

    text += message;

    std::printf(text.c_str());

    text.clear();
}
