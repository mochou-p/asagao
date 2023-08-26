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

    glm::mat4 projection = glm::ortho(-4.8f, 4.8f, -4.5f, 4.5f);
    shader.set_mat4("u_mvp", projection);

    IndexBuffer saber_ib(saber_indices,
        sizeof(saber_indices) / sizeof(GLuint));
    Texture saber_tex("saber.png");
    objects.push_back("saber");

    IndexBuffer gudako_ib(gudako_indices,
        sizeof(gudako_indices) / sizeof(GLuint));
    Texture gudako_tex("gudako.png");
    objects.push_back("gudako");

    glm::vec2 camera {0.0f, 0.0f};
    glm::vec2 aspect;

    bool view_changed = false;

    while (window.is_open())
    {
        window.poll_events();

        renderer.clear();

        if (moving.x)
        {
            camera.x += moving.x * Renderer::zoom;
            view_changed = true;
        }

        if (moving.y)
        {
            camera.y += moving.y * Renderer::zoom;
            view_changed = true;
        }

        if (window.was_resized || renderer.was_resized)
        {
            aspect = (window.size * Layout::scene.size) * renderer.zoom;

            window.was_resized   = false;
            renderer.was_resized = false;
            view_changed         = true;
        }

        if (view_changed)
        {
            projection = glm::ortho
            (
               -aspect.x + camera.x,
                aspect.x + camera.x,
               -aspect.y + camera.y,
                aspect.y + camera.y
            );

            shader.set_mat4("u_mvp", projection);

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
