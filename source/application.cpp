// asagao/source/application.cpp


#include "stdafx.h"

#include "asagao.hpp"

#include "rect.hpp"
#include "vertex_buffer.hpp"
#include "vertex_buffer_layout.hpp"
#include "vertex_array.hpp"
#include "index_buffer.hpp"
#include "game_object.hpp"
#include "benchmark.hpp"


namespace Asagao
{
    void
    Application::run(const str& argv_scene)
    {
        shader = std::make_unique<Shader>("atlas.glsl");

        Rect quad(rect_size);

        VertexBufferLayout layout;
        layout.push(2, GL_FLOAT);  // position
        layout.push(2, GL_FLOAT);  // texcoord

        VertexBuffer vb(quad);

        VertexArray va;
        va.add_vertex_buffer(layout);

        IndexBuffer ib(quad);

        Window.resize();

        u32 animation_time;

        if (argv_scene != str())
            scene = std::make_unique<Scene>(argv_scene);

        while (Window.is_open())
        {
            Window.poll_events();
            Renderer.clear();

            if (scene)
            {
                // Benchmark _("Scene render");

                animation_time = Window.get_time() * animation_speed;

                for (const GameObject& obj : scene->objects)
                {
                    if (!obj.visible)
                        continue;

                    shader->set_mat4("u_mvp",     Camera.get_mvp(obj));
                    shader->set_vec2("u_tile_uv", obj.get_uv(animation_time));

                    Renderer.draw();
                }
            }

            Interface.draw();
            Window.swap_buffers();
        }
    }
}  // Asagao::
