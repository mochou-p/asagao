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
    //  position       | texcoord
    //  x       y      | u     v
       -128.0f, -128.0f,   0.0f, 0.0f,
        128.0f, -128.0f,   1.0f, 0.0f,
        128.0f,  128.0f,   1.0f, 1.0f,
       -128.0f,  128.0f,   0.0f, 1.0f,
    };

    const unsigned int indices[]
    {
        0, 1, 2,
        2, 3, 0
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

    IndexBuffer ib(indices, sizeof(indices) / sizeof(unsigned int));

    Shader shader("test.glsl");
    shader.use();

    const glm::mat4 mat4_identity(1.0f);
    const glm::vec3 z_axis(0.0f, 0.0f, 1.0f);

    glm::mat4 model, view, projection;

    objects.push_back({"Saber",  {-138.0f, 0.0f},  "saber.png"});
    objects.push_back({"Gudako", { 138.0f, 0.0f}, "gudako.png"});

    while (window.is_open())
    {
        window.poll_events();

        renderer.clear();

        projection = glm::ortho(-aspect.x, aspect.x, -aspect.y, aspect.y);
        view       = glm::translate(mat4_identity, camera);

        for (const GameObject& obj : objects)
        {
            if (!obj.visible) continue;

            model = glm::translate(mat4_identity, obj.position);
            model = glm::rotate(model, glm::radians(obj.rotation), z_axis);
            model = glm::scale(model, obj.scale);

            shader.set_mat4("u_mvp", projection * view * model);

            shader.set_int("u_texture", obj.tex->get_slot());

            renderer.draw(va, ib, shader);
        }

        ui.draw();

        window.swap_buffers();
    }
}

void
Application::new_object()
{
    static unsigned int i = 0;

    objects.push_back({"Unnamed " + std::to_string(++i), {0.0f, 0.0f},
        "default.png"});
}
