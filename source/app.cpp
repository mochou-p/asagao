// asagao/source/app.cpp


#include <iostream>
#include "app.hpp"
#include "shader.hpp"
#include "utils.hpp"
#include "texture.hpp"
#include "objects.hpp"

App::App(const std::string& name,
               int          width,
               int          height)
{
    m_window    = std::make_unique<Window>(name, width, height);
    m_interface = std::make_unique<Gui>();
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

void
App::run()
{
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(debug_message_callback, nullptr);

    const float vertices[]
    {
    //  position     | texcoords
    //  x      y     | u     v
       -0.2f, -0.2f,   0.0f, 0.0f,
        0.2f, -0.2f,   1.0f, 0.0f,
        0.2f,  0.2f,   1.0f, 1.0f,
       -0.2f,  0.2f,   0.0f, 1.0f
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

    loop();
}

void
App::loop()
{
    while (m_window->is_open())
    {
        m_window->events();
        m_window->clear();

        //                           |
        // count of indices (temp)   V
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        m_interface->draw();

        m_window->swap_buffers();
    }
}
