// asagao/source/renderer.cpp


#include <iostream>
#include "renderer.hpp"
#include "window.hpp"

static void
load_opengl_functions()
{
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        quit("gladLoadGLLoader failed");

    std::cout << "OpenGL\t" << glGetString(GL_VERSION) << std::endl;
}

static void GLAPIENTRY
debug_message_callback([[maybe_unused]]       GLenum  source,
                                              GLenum  type,
                       [[maybe_unused]]       GLuint  id,
                                              GLenum  severity,
                       [[maybe_unused]]       GLsizei length,
                                        const GLchar* message,
                       [[maybe_unused]] const void*   param)
{
    std::cout
        << '('   << "type     = 0x" << std::hex << type
        << "\n " << "severity = 0x" << std::hex << severity
        << "\n " << "message  = "   <<             message
        << ')'   << std::endl;
}

Renderer::Renderer()
{
    if (instance) quit("only one instance of renderer is allowed");

    instance = this;
}

void
Renderer::init()
{
    load_opengl_functions();

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(debug_message_callback, nullptr);
}

void
Renderer::draw(VertexArray& va,
               IndexBuffer& ib,
               Shader&      shader)
{
    shader.use();
    va.bind();
    ib.bind();

    glDrawElements(GL_TRIANGLES, ib.get_count(), GL_UNSIGNED_INT, nullptr);
}
