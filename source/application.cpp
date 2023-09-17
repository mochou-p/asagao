// asagao/source/application.cpp


#include "application.hpp"
#include "texture.hpp"
#include "window.hpp"
#include "interface.hpp"
#include "gtc/matrix_transform.hpp"
#include "style.hpp"
#include "sprite_atlas.hpp"
#include "rect.hpp"

#define APP_NAME "Asagao"
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

void
Application::run()
{
    Renderer  renderer;
    Window    window(APP_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);
    Interface ui;

    Shader      shader("atlas.glsl");
    SpriteAtlas atlas("kenney-pixel-platformer.png", 18);

    Rect quad(rect_size, uv_fraction);

    VertexBuffer       vb(quad);
    VertexBufferLayout layout;
    layout.push(2, GL_FLOAT);  // position
    layout.push(2, GL_FLOAT);  // texcoord

    VertexArray va;
    va.add_vertex_buffer(vb, layout);

    IndexBuffer ib(quad);

    renderer.set_background_color({0.875f, 0.965f, 0.961f, 1.0f});

    shader.use();
    shader.set_int("u_texture", atlas.texture->get_slot());

    unsigned int animation_time;

    while (window.is_open())
    {
        window.poll_events();
        renderer.clear();

        if (scene)
        {
            animation_time = glfwGetTime() * animation_speed;

            for (const GameObject& obj : scene->objects)
            {
                if (!obj.visible) continue;

                shader.set_mat4("u_mvp",     camera.get_mvp(obj));
                shader.set_vec2("u_tile_uv", obj.get_uv(animation_time));

                renderer.draw(va, ib, shader);
            }
        }

        ui.draw();
        window.swap_buffers();
    }
}
