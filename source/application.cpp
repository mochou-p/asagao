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

    // demo scene
    objects.push_back
    ({"Mountains", {   0.0f,  250.0f}, "mountains.png", {20.0f, 6.0f}, 10.0f});
    objects.push_back
    ({"Road",      {   0.0f, -650.0f},      "road.png", {8.0f, 2.0f}});
    objects.push_back
    ({"Birds",     {-315.0f,  200.0f},     "birds.png", {5.0f, 4.0f}, 3.0f});
    objects.push_back
    ({"Birds",     { 115.0f,  100.0f},     "birds.png", {3.0f, 2.0f}, 5.0f});
    objects.push_back
    ({"Saber",     {-600.0f, -435.0f},     "saber.png", {2.0f, 3.0f}});
    objects.push_back
    ({"Gudako",    { 450.0f, -435.0f},    "gudako.png", {2.0f, 2.2f}});

    while (window.is_open())
    {
        window.poll_events();

        renderer.clear();

        projection = glm::ortho(-aspect.x, aspect.x, -aspect.y, aspect.y);

        for (const GameObject& obj : objects)
        {
            if (!obj.visible) continue;

            view  = glm::translate
            (mat4_identity, camera * (1.0f - obj.depth * 0.2f));

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
