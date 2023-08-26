// asagao/source/application.cpp


#include <iostream>
#include "application.hpp"
#include "texture.hpp"
#include "renderer.hpp"
#include "window.hpp"
#include "interface.hpp"
#include "gtc/matrix_transform.hpp"
#include "style.hpp"

#define APP_NAME "Asagao"
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

void
Application::run() const
{
    const float vertices[]
    {
    //  position     | texcoord
    //  x      y     | u     v

    // saber
       -4.0f, -1.0f,   0.0f, 0.0f,
       -2.0f, -1.0f,   1.0f, 0.0f,
       -2.0f,  1.0f,   1.0f, 1.0f,
       -4.0f,  1.0f,   0.0f, 1.0f,
    // gudako
        2.0f, -1.0f,   0.0f, 0.0f,
        4.0f, -1.0f,   1.0f, 0.0f,
        4.0f,  1.0f,   1.0f, 1.0f,
        2.0f,  1.0f,   0.0f, 1.0f
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

    Renderer renderer;

    Window window(APP_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);
    Interface ui;

    VertexBuffer vb(vertices, sizeof(vertices));

    VertexBufferLayout layout;
    layout.push(2, GL_FLOAT);  // position
    layout.push(2, GL_FLOAT);  // texcoord

    VertexArray va;
    va.add_vertex_buffer(vb, layout);

    Shader shader("test.glsl");
    shader.use();

    IndexBuffer saber_ib(saber_indices,
        sizeof(saber_indices) / sizeof(GLuint));
    Texture saber_tex("saber.png");
    objects.push_back("saber");

    IndexBuffer gudako_ib(gudako_indices,
        sizeof(gudako_indices) / sizeof(GLuint));
    Texture gudako_tex("gudako.png");
    objects.push_back("gudako");

    aspect = (window.size * Layout::scene.size) * renderer.zoom;

    while (window.is_open())
    {
        window.poll_events();

        renderer.clear();

        if (view_changed)
        {
            shader.set_mat4
            (
                "u_mvp",
                glm::ortho
                (
                   -aspect.x + camera.x,
                    aspect.x + camera.x,
                   -aspect.y + camera.y,
                    aspect.y + camera.y
                )
            );

            view_changed = false;
        }

        shader.set_int("u_texture", saber_tex.get_slot());
        renderer.draw(va, saber_ib, shader);
        shader.set_int("u_texture", gudako_tex.get_slot());
        renderer.draw(va, gudako_ib, shader);

        ui.draw();

        window.swap_buffers();
    }
}
