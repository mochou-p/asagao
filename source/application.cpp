// asagao/source/application.cpp


#include "stdafx.h"

#include "asagao.hpp"

#include "rect.hpp"
#include "vertex_buffer.hpp"
#include "vertex_buffer_layout.hpp"
#include "vertex_array.hpp"
#include "index_buffer.hpp"
#include "game.hpp"


namespace Asagao
{
    void
    Application::run()
    {
        shader = std::make_unique<Shader>("tile.glsl");
        shader->set_int("u_texture", 0);  // GL_TEXTURE0 only

        Rect quad(rect_size);

        VertexBufferLayout layout;
        layout.push(2, GL_FLOAT);  // position
        layout.push(2, GL_FLOAT);  // texcoord

        VertexBuffer vb(quad);

        VertexArray va;
        va.add_vertex_buffer(layout);

        IndexBuffer ib(quad);

        Window.resize();

        Game game;
        bool f5_pressed;

        while (Window.is_open())
        {
            Window.poll_events();
            Renderer.clear();

            if (game.running)
                game.update();
            else
            {
                if (!f5_pressed && Input::is_down(Key::F5))
                    f5_pressed ^= 1;

                if (f5_pressed && !Input::is_down(Key::F5))
                {
                    game.start();
                    game.running ^= 1;
                }
            }

            if (scene)
                scene->draw();

            Interface.draw();
            Window.swap_buffers();
        }
    }
}  // Asagao::
