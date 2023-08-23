// asagao/source/app.cpp


#include <iostream>
#include <cmath>
#include "app.hpp"
#include "shader.hpp"
#include "utils.hpp"
#include "texture.hpp"
#include "objects.hpp"

App::App(const std::string& t_name, int t_width, int t_height)
{
    m_win = std::make_unique<Window>(t_name, t_width, t_height);
    m_gui = std::make_unique<Gui>();
}

void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 [[maybe_unused]] GLuint id,
                 GLenum severity,
                 [[maybe_unused]] GLsizei length,
                 const GLchar* message,
                 [[maybe_unused]] const void* userParam )
{
  fprintf( stderr,
    "GL LOG: %s source=0x%x, type=0x%x, severity=0x%x, message=%s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            source, type, severity, message );
}

void App::run()
{
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);

    const float vertices[]
    {
    //  position     | texcoords
    //  x      y     | u    v
       -0.2f, -0.2f,   0,   0,
        0.2f, -0.2f,   1,   0,
        0.2f,  0.2f,   1,   1,
       -0.2f,  0.2f,   0,   1
    };

    const GLuint indices[]
    {
        0, 1, 2,
        2, 3, 0
    };

    VAP  position(2, 4 * sizeof(float), 0);
    VAP texcoords(2, 4 * sizeof(float), 2 * sizeof(float));
    VAO vao({position, texcoords});

    BO vbo((void*) vertices, sizeof(vertices), GL_ARRAY_BUFFER);
    BO ebo((void*) indices,  sizeof(indices),  GL_ELEMENT_ARRAY_BUFFER);

    Shader test_shader("test.glsl");
    Texture saber_tex("saber.png");
    test_shader.set_int("u_texture", saber_tex.get_order());

    vao.enable();
    test_shader.use();

    const GLsizei count = sizeof(indices) / sizeof(GLuint);

    while (m_win->is_open())
    {
        m_win->events();
        m_win->clear();

        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);

        m_gui->draw();

        m_win->swap_buffers();
    }
}
