// asagao/source/application.cpp


#include <iostream>
#include "application.hpp"
#include "texture.hpp"
#include "window.hpp"
#include "interface.hpp"
#include "gtc/matrix_transform.hpp"
#include "style.hpp"

#define APP_NAME "Asagao"
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

void
Application::run()
{
    const float vertices[]
    {
    //  position       | texcoord
    //  x       y      | u     v
       -50.0f, -50.0f,   0.0f, 0.0f,
        50.0f, -50.0f,   1.0f, 0.0f,
        50.0f,  50.0f,   1.0f, 1.0f,
       -50.0f,  50.0f,   0.0f, 1.0f,
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

    load_demo_scene(2, renderer);

    unsigned int animation_time;

    while (window.is_open())
    {
        window.poll_events();

        animation_time = glfwGetTime() * animation_speed;

        projection = glm::ortho
        (
            -aspect.x, aspect.x,
            -aspect.y, aspect.y,
            -1000.0f,  1000.0f
        );

        renderer.clear();

        for (const GameObject& obj : objects)
        {
            if (!obj.visible) continue;

            view  = glm::translate
            (
                mat4_identity,
                camera - (camera * obj.depth * 0.08f)
            );

            model = glm::translate(mat4_identity, obj.position);
            model = glm::rotate(model, glm::radians(obj.rotation), z_axis);
            model = glm::scale(model, obj.scale);

            shader.set_mat4("u_mvp", projection * view * model);

            shader.set_int
            (
                "u_texture",
                obj.textures[animation_time % obj.texture_count]->get_slot()
            );

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
        {"textures/default.png"}});
}

void
Application::load_demo_scene
(
 unsigned int    id,
 const Renderer& renderer
)
{
    switch (id)
    {
    case 1:
        objects.push_back
        ({
            "Mountains",
            {0.0f,  250.0f},
            {"textures/mountains.png"},
            {20.0f, 6.0f},
            10.0f
        });

        objects.push_back
        ({
            "Birds 1",
            {350.0f,  100.0f},
            {"textures/birds.png"},
            {3.0f, 2.0f},
            5.0f
        });

        objects.push_back
        ({
            "Birds 2",
            {-630.0f,  200.0f},
            {"textures/birds.png"},
            {5.0f, 4.0f},
            3.0f
        });

        objects.push_back
        ({
            "Road",
            {0.0f, -650.0f},
            {"textures/road.png"},
            {30.0f, 2.0f}
        });

        objects.push_back
        ({
            "Saber",
            {-600.0f, -435.0f},
            {"textures/saber.png"},
            {2.0f, 3.0f}
        });

        objects.push_back
        ({
            "Gudako",
            {450.0f, -435.0f},
            {"textures/gudako.png"},
            {2.0f, 2.2f}
        });

        objects.push_back
        ({
            "Plane",
            {2550.0f, 0.0f},
            {"textures/plane.png"},
            {10.0f, 5.0f},
            -100.0f
        });

        break;
    case 2:
        renderer.set_background_color
        ({
            223.0f / 255.0f,
            246.0f / 255.0f,
            245.0f / 255.0f,
            1.0f
        });

        objects.push_back
        ({
            "Cloud 1",
            {-240.0f, 600.0f},
            {"tiles/cloudL.png"},
            {0.8f, 0.8f},
            7.0f
        });
        objects.push_back
        ({
            "Cloud 2",
            {-160.0f, 600.0f},
            {"tiles/cloudC.png"},
            {0.8f, 0.8f},
            7.0f
        });
        objects.push_back
        ({
            "Cloud 3",
            {-80.0f, 600.0f},
            {"tiles/cloudR.png"},
            {0.8f, 0.8f},
            7.0f
        });

        objects.push_back
        ({
            "Cloud 4",
            {300.0f, 400.0f},
            {"tiles/cloudL.png"},
            {1.0f, 1.0f}, 5.0f
        });
        objects.push_back
        ({
            "Cloud 5",
            {400.0f, 400.0f},
            {"tiles/cloudC.png"},
            {1.0f, 1.0f},
            5.0f
        });
        objects.push_back
        ({
            "Cloud 6",
            {500.0f, 400.0f},
            {"tiles/cloudR.png"},
            {1.0f, 1.0f},
            5.0f
        });

        objects.push_back
        ({
            "Cloud 7",
            {-600.0f, -100.0f},
            {"tiles/cloudL.png"},
            {1.0f, 1.0f}, 5.0f
        });
        objects.push_back
        ({
            "Cloud 8",
            {-500.0f, -100.0f},
            {"tiles/cloudC.png"},
            {1.0f, 1.0f},
            5.0f
        });
        objects.push_back
        ({
            "Cloud 9",
            {-400.0f, -100.0f},
            {"tiles/cloudR.png"},
            {1.0f, 1.0f},
            5.0f
        });

        objects.push_back
        ({
            "Fly 1",
            {130.0f, 270.0f},
            {"tiles/fly0.png", "tiles/fly1.png",
             "tiles/fly2.png", "tiles/fly1.png"},
            {0.9f, 0.9f},
            2.0f
        });

        objects.push_back
        ({
            "Fly 2",
            {240.0f, 200.0f},
            {"tiles/fly1.png", "tiles/fly2.png",
             "tiles/fly1.png", "tiles/fly0.png"},
            {1.0f, 1.0f},
            2.0f
        });

        objects.push_back
        ({
            "Player",
            {-100.0f, 0.0f},
            {"tiles/player0.png", "tiles/player1.png"}
        });

        objects.push_back({"Spikes", {50.0f, 0.0f}, {"tiles/spikes.png"}});

        objects.push_back({"Ground 1", {-100.0f, -100.0f}, {"tiles/TL.png"}});
        objects.push_back({"Ground 2", {   0.0f, -100.0f}, {"tiles/TC.png"}});
        objects.push_back({"Ground 3", { 100.0f, -100.0f}, {"tiles/TR.png"}});
        objects.push_back({"Ground 4", {-100.0f, -200.0f}, {"tiles/CL.png"}});
        objects.push_back({"Ground 5", {   0.0f, -200.0f}, {"tiles/CC.png"}});
        objects.push_back({"Ground 6", { 100.0f, -200.0f}, {"tiles/CR.png"}});
        objects.push_back({"Ground 7", {-100.0f, -300.0f}, {"tiles/BL.png"}});
        objects.push_back({"Ground 8", {   0.0f, -300.0f}, {"tiles/BC.png"}});
        objects.push_back({"Ground 9", { 100.0f, -300.0f}, {"tiles/BR.png"}});

    default:
        break;
    }
}
