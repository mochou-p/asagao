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

GameObject::GameObject
(
 const std::string&            name,
 const glm::vec2&              position,
 const std::vector<glm::vec2>& tile_offsets,
       float                   rotation = 0.0f
)
:         name{name}
,     position{
               position.x * Application::rect_size,
               position.y * Application::rect_size,
               0.0f
              }
,        depth{0.0f}
,        scale{1.0f, 1.0f, 1.0f}
,     rotation{rotation}
,      visible{true}
, sprite_count{tile_offsets.size()}
{
    for (const glm::vec2& o : tile_offsets)
        sprite_offsets.push_back(o * Application::uv_frac);
}

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
    SpriteAtlas     atlas("atlases/tiles.png", 18);


    uv_frac = atlas.sprite_uv_frac;

    //  x, y
    //  u, v
    const float vertices[]
    {
       -rect_size * 0.5f,       -rect_size * 0.5f,
        0.0f,                    0.0f,

        rect_size * 0.5f,       -rect_size * 0.5f,
        atlas.sprite_uv_frac.x,  0.0f,

        rect_size * 0.5f,        rect_size * 0.5f,
        atlas.sprite_uv_frac.x,  atlas.sprite_uv_frac.y,

       -rect_size * 0.5f,        rect_size * 0.5f,
        0.0f,                    atlas.sprite_uv_frac.y,
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


    load_demo_scene(renderer);

    shader.use();
    shader.set_int("u_texture", atlas.texture->get_slot());


    while (window.is_open())
    {
        window.poll_events();

        animation_time = glfwGetTime() * animation_speed;

        projection = glm::ortho(-aspect.x, aspect.x, -aspect.y, aspect.y);

        renderer.clear();

        for (const GameObject& obj : objects)
        {
            if (!obj.visible) continue;

            view = glm::translate
            (
                mat4_identity,
                camera - (camera * obj.depth * 0.08f)
            );

            model     = glm::translate(mat4_identity, obj.position);
            model     = glm::rotate(model, glm::radians(obj.rotation), z_axis);
            model     = glm::scale(model, obj.scale);
            sprite_id = animation_time % obj.sprite_count;

            shader.set_mat4("u_mvp",     projection * view * model);
            shader.set_vec2("u_tile_uv", obj.sprite_offsets[sprite_id]);

            renderer.draw(va, ib, shader);
        }

        ui.draw();

        window.swap_buffers();
    }
}

// temp
void
Application::load_demo_scene
(
 const Renderer&    renderer
)
{
    renderer.set_background_color
    ({
        223.0f / 255.0f,
        246.0f / 255.0f,
        245.0f / 255.0f,
        1.0f
    });

    glm::vec2  diamond(7, 5);
    glm::vec2   cactus(7, 2);
    glm::vec2 platform(6, 1);
    glm::vec2    spike(8, 5);
    glm::vec2     sand(0, 5);

    glm::vec2 block[] =
    {
        {9, 8}, {10, 8}, {8, 7}
    };
    glm::vec2 grass[] =
    {
        {1, 7}, {2, 7}, {3, 7}
    };
    glm::vec2 snow[] =
    {
        {1, 4}, {2, 4}, {3, 4}
    };
    glm::vec2 dirt[] =
    {
        {1, 2}, {2, 2}, {3, 2},
        {1, 1}, {2, 1}, {3, 1},
        {0, 2}, {4, 7}, {5, 7}
    };
    glm::vec2 water[] =
    {
        {13, 7}, {13, 6},
        {13, 5}
    };
    glm::vec2 flag[] =
    {
        {11, 3}, {12, 3},
        {11, 2}
    };
    glm::vec2 coin[] =
    {
        {11, 1}, {12, 1}
    };
    glm::vec2 door[] =
    {
        {10, 2}, {10, 3}
    };
    glm::vec2 cloud[] =
    {
        {13, 1}, {14, 1}, {15, 1}
    };
    glm::vec2 weed[] =
    {
        {4, 2}, {5, 2}, {4, 1}
    };
    glm::vec2 tree[] =
    {
        {17, 2}, {18, 2}, {19, 2},
        {16, 3}, {16, 4}
    };
    glm::vec2 leaf[] =
    {
        {17, 8}, {18, 8}, {19, 8},
        {17, 6}, {17, 4}, {19, 6},
        {16, 8}
    };


    objects.push_back({"Leaf    1", {-2, 5}, {leaf[0]}});
    objects.push_back({"Leaf    2", {-1, 5}, {leaf[1]}});
    objects.push_back({"Leaf    3", { 0, 5}, {leaf[2]}});

    objects.push_back({"Leaf    4", {-1.5f, 5.2f}, {leaf[6]}});

    objects.push_back({"Leaf    5", {-2, 4}, {leaf[3]}});
    objects.push_back({"Leaf    6", {-1, 4}, {leaf[4]}});
    objects.push_back({"Leaf    7", { 0, 4}, {leaf[5]}});

    objects.push_back({"Tree    1", {-1, 3}, {tree[4]}});

    objects.push_back({"Tree    2", {-1, 2}, {tree[1]}});
    objects.push_back({"Tree    3", { 0, 2}, {tree[2]}});

    objects.push_back({"Coin    1", {1.5f, 2.5f}, {coin[0], coin[1]}});

    objects.push_back({"Tree    4", {-1, 1}, {tree[0]}});
    objects.push_back({"Weed    1", { 0, 1}, {weed[0]}});
    objects.push_back({"Weed    2", {-2, 1}, {weed[1]}});
    objects.push_back({"Cactus  1", { 3, 1}, {cactus}});

    objects.push_back({"Grass   1", {-2,  0   }, {grass[0]}});
    objects.push_back({"Grass   2", {-1,  0   }, {grass[1]}});
    objects.push_back({"Grass   3", { 0,  0   }, {grass[2]}});
    objects.push_back({"Water   1", { 1, -0.3f}, {water[0], water[1]}});
    objects.push_back({"Water   2", { 2, -0.3f}, {water[0], water[1]}});
    objects.push_back({"Sand    1", { 3,  0   }, {sand}});

    objects.push_back({"Dirt    1", {-2, -1}, {dirt[0]}});
    objects.push_back({"Dirt    2", {-1, -1}, {dirt[1]}});
    objects.push_back({"Dirt    3", { 0, -1}, {dirt[2]}});
    objects.push_back({"Water   3", { 1, -1}, {water[2]}});
    objects.push_back({"Water   4", { 2, -1}, {water[2]}});
    objects.push_back({"Dirt    4", { 3, -1}, {dirt[6]}});

    objects.push_back({"Dirt    5", {-2, -2}, {dirt[0]}});
    objects.push_back({"Dirt    6", {-1, -2}, {dirt[1]}});
    objects.push_back({"Dirt    7", { 0, -2}, {dirt[1]}});
    objects.push_back({"Dirt    8", { 1, -2}, {dirt[4]}, 180});
    objects.push_back({"Dirt    9", { 2, -2}, {dirt[4]}, 180});
    objects.push_back({"Dirt   10", { 3, -2}, {dirt[2]}});

    objects.push_back({"Dirt   11", {-2, -3}, {dirt[3]}});
    objects.push_back({"Dirt   12", {-1, -3}, {dirt[4]}});
    objects.push_back({"Dirt   13", { 0, -3}, {dirt[4]}});
    objects.push_back({"Dirt   14", { 1, -3}, {dirt[4]}});
    objects.push_back({"Dirt   15", { 2, -3}, {dirt[4]}});
    objects.push_back({"Dirt   16", { 3, -3}, {dirt[5]}});

    (void)(block);
    (void)(snow);
    (void)(flag);
    (void)(door);
    (void)(cloud);
}
