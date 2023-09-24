// asagao/source/application.cpp


#include "asagao.hpp"

#include "shader.hpp"
#include "sprite_atlas.hpp"
#include "rect.hpp"
#include "vertex_buffer.hpp"
#include "vertex_buffer_layout.hpp"
#include "vertex_array.hpp"
#include "index_buffer.hpp"
#include "game_object.hpp"

namespace Asagao
{
    void
    Application::run() const
    {
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

        Renderer.set_background_color({0.875f, 0.965f, 0.961f, 1.0f});

        shader.use();
        shader.set_int("u_texture", atlas.texture->get_slot());

        unsigned int animation_time;

        Window.resize();

        while (Window.is_open())
        {
            Window.poll_events();
            Renderer.clear();

            if (scene)
            {
                animation_time = Window.get_time() * animation_speed;

                for (const GameObject& obj : scene->objects)
                {
                    if (!obj.visible) continue;

                    shader.set_mat4("u_mvp",     Camera.get_mvp(obj));
                    shader.set_vec2("u_tile_uv", obj.get_uv(animation_time));

                    Renderer.draw(va, ib, shader);
                }
            }

            Interface.draw();
            Window.swap_buffers();
        }
    }
}  // Asagao::
