// asagao/source/app.cpp


#include <iostream>
#include "app.hpp"
#include "texture.hpp"
#include "renderer.hpp"

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

    // saber
       -0.5f, -0.2f,   0.0f, 0.0f,
       -0.3f, -0.2f,   1.0f, 0.0f,
       -0.3f,  0.2f,   1.0f, 1.0f,
       -0.5f,  0.2f,   0.0f, 1.0f,
    // gudako
        0.3f, -0.2f,   0.0f, 0.0f,
        0.5f, -0.2f,   1.0f, 0.0f,
        0.5f,  0.2f,   1.0f, 1.0f,
        0.3f,  0.2f,   0.0f, 1.0f
    };

    const GLuint saber_indices[]
    {
        0, 1, 2,
        2, 3, 0
    };

    const GLuint gudako_indices[]
    {
        4, 5, 6,
        6, 7, 4
    };

    VertexArray va;
    VertexBuffer vb(vertices, sizeof(vertices));

    VertexBufferLayout layout;
    layout.push(2, GL_FLOAT);  // position
    layout.push(2, GL_FLOAT);  // texcoords
    va.add_vertex_buffer(vb, layout);

    Shader shader("test.glsl");

    IndexBuffer saber_ib(saber_indices,
        sizeof(saber_indices) / sizeof(GLuint));
    Texture     saber_tex("saber.png");

    IndexBuffer gudako_ib(gudako_indices,
        sizeof(gudako_indices) / sizeof(GLuint));
    Texture     gudako_tex("gudako.png");

    Renderer renderer;

    while (m_window->is_open())
    {
        m_window->events();

        renderer.clear();

        shader.set_int("u_texture", saber_tex.get_order());
        renderer.draw(va, saber_ib, shader);
        shader.set_int("u_texture", gudako_tex.get_order());
        renderer.draw(va, gudako_ib, shader);

        m_interface->draw();

        m_window->swap_buffers();
    }
}
