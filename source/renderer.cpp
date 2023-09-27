// asagao/source/renderer.cpp


#include "stdafx.h"

#include "renderer.hpp"
#include "log.hpp"
#include "shader.hpp"
#include "vertex_array.hpp"
#include "index_buffer.hpp"


static void load_opengl_functions();

static void GLAPIENTRY debug_message_callback(u32 source, u32 type, u32 id, u32 severity, i32 length, c_cstr message, const void* param);


namespace Asagao
{
    void
    Renderer::init()
    {
        load_opengl_functions();

        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(debug_message_callback, nullptr);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
    }

    void
    Renderer::clear() const
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void
    Renderer::draw
    (const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
    {
        shader.use();
        va.bind();
        ib.bind();

        glDrawElements(GL_TRIANGLES, ib.get_count(), GL_UNSIGNED_INT, nullptr);
    }

    void
    Renderer::set_background_color
    (const v4& color) const
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }
}  // Asagao::


static void
load_opengl_functions()
{
    assert(gladLoadGLLoader((GLADloadproc) glfwGetProcAddress));

    LOG_INFO(str("OpenGL ") + (c_cstr) glGetString(GL_VERSION));
}

static void GLAPIENTRY
debug_message_callback
(u32 source, u32 type, u32 id, u32 severity, i32 length, c_cstr message, const void* param)
{
    LOG_AUTO(severity, message);
}
