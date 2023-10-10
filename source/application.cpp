// asagao/source/application.cpp


#include "stdafx.h"

#include "asagao.hpp"

#include "rect.hpp"
#include "vertex_buffer.hpp"
#include "vertex_buffer_layout.hpp"
#include "vertex_array.hpp"
#include "index_buffer.hpp"


namespace Asagao
{
    void
    Application::run
    (const str& argv_scene)
    {
        shader = std::make_unique<Shader>("tile.glsl");

        Rect quad(rect_size);

        VertexBufferLayout layout;
        layout.push(2, GL_FLOAT);  // position
        layout.push(2, GL_FLOAT);  // texcoord

        VertexBuffer vb(quad);

        VertexArray va;
        va.add_vertex_buffer(layout);

        IndexBuffer ib(quad);

        Window.resize();

        if (argv_scene != str())
            scene = std::make_unique<Scene>(argv_scene);

        while (Window.is_open())
        {
            Window.poll_events();
            Renderer.clear();

            if (scene)
                scene->draw();

            Interface.draw();
            Window.swap_buffers();
        }
    }
}  // Asagao::
