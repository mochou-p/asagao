// asagao/source/renderer.cpp


#include "renderer.hpp"
#include "log.hpp"

#include "glad.h"
#include "glfw3.h"

static void
load_opengl_functions()
{
    assert(gladLoadGLLoader((GLADloadproc) glfwGetProcAddress));

    LOG_INFO(std::string("OpenGL ") + (const char*) glGetString(GL_VERSION));
}

static void GLAPIENTRY
debug_message_callback
(
       unsigned int source,
       unsigned int type,
       unsigned int id,
       unsigned int severity,
       int          length,
 const char*        message,
 const void*        param
)
{
    LOG_AUTO(severity, message);
}

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
    (
    const VertexArray& va,
    const IndexBuffer& ib,
    const Shader&      shader
    ) const
    {
        shader.use();
        va.bind();
        ib.bind();

        glDrawElements(GL_TRIANGLES, ib.get_count(), GL_UNSIGNED_INT, nullptr);
    }

    void
    Renderer::set_background_color(const glm::vec4& color) const
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }
}  // Asagao::
