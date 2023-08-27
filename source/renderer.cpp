// asagao/source/renderer.cpp


#include <iostream>
#include "renderer.hpp"
#include "glfw3.h"

static void
load_opengl_functions()
{
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        quit("gladLoadGLLoader failed");
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
    std::cout
        << '('   << "type     = 0x" << std::hex << type
        << "\n " << "severity = 0x" << std::hex << severity
        << "\n " << "message  = "   <<             message
        << ')'   << std::endl;

    (void)(source);
    (void)(id);
    (void)(length);
    (void)(param);
}

void
Renderer::init()
{
    load_opengl_functions();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debug_message_callback, nullptr);
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
