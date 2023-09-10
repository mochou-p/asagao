// asagao/source/application.cpp


#include "application.hpp"
#include "texture.hpp"
#include "window.hpp"
#include "interface.hpp"
#include "gtc/matrix_transform.hpp"
#include "style.hpp"
#include "sprite_atlas.hpp"

#define APP_NAME "Asagao"
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

void
Application::run()
{
    glm::mat4       model, view, projection;
    unsigned int    animation_time;
    unsigned int    sprite_id;

    const glm::mat4 mat4_identity(1.0f);
    const glm::vec3 z_axis(0.0f, 0.0f, 1.0f);

    Renderer        renderer;
    Window          window(APP_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);
    Interface       ui;
    Shader          shader("atlas.glsl");
    SpriteAtlas     atlas("kenney_pixel-platformer.png", 18);


    const float vertices[]
    {
       -rect_size * 0.5f,   -rect_size * 0.5f, // x, y
        0.0f,               0.0f,              // u, v

        rect_size * 0.5f,   -rect_size * 0.5f,
        uv_frac.x,          0.0f,

        rect_size * 0.5f,   rect_size * 0.5f,
        uv_frac.x,          uv_frac.y,

       -rect_size * 0.5f,   rect_size * 0.5f,
        0.0f,               uv_frac.y,
    };

    VertexBuffer vb(vertices, sizeof(vertices));

    VertexBufferLayout layout;
    layout.push(2, GL_FLOAT);  // position
    layout.push(2, GL_FLOAT);  // texcoord

    VertexArray va;
    va.add_vertex_buffer(vb, layout);


    const unsigned int indices[]
    {
        0, 1, 2,
        2, 3, 0
    };

    IndexBuffer ib(indices, sizeof(indices) / sizeof(unsigned int));


    renderer.set_background_color
    ({
        223.0f / 255.0f,
        246.0f / 255.0f,
        245.0f / 255.0f,
        1.0f
    });


    shader.use();
    shader.set_int("u_texture", atlas.texture->get_slot());


    while (window.is_open())
    {
        window.poll_events();

        if (scene)
        {
            animation_time = glfwGetTime() * animation_speed;

            projection = glm::ortho(-aspect.x, aspect.x, -aspect.y, aspect.y);

            renderer.clear();

            for (const GameObject& obj : scene->objects)
            {
                if (!obj.visible) continue;

                view = glm::translate
                (
                    mat4_identity,
                    camera - (camera * obj.depth * 0.08f)
                );

                model = glm::translate(mat4_identity, obj.position);
                model = glm::rotate(model, glm::radians(obj.rotation), z_axis);
                model = glm::scale(model, obj.scale);

                sprite_id = animation_time % obj.sprite_count;

                shader.set_mat4("u_mvp",     projection * view * model);
                shader.set_vec2("u_tile_uv", obj.sprite_offsets[sprite_id]);

                renderer.draw(va, ib, shader);
            }
        }

        ui.draw();

        window.swap_buffers();
    }
}
