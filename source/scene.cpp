// asagao/source/scene.cpp


#include "stdafx.h"

#include "asagao.hpp"

#include "scene.hpp"
#include "application.hpp"
#include "log.hpp"


#define SCENE_PATH       "resources/scenes"
#define SCENE_EXT        ".asagao"
#define SCENE_VER        "0.0.1"
#define SCENE_HEADER_TOP "### Asagao Scene File ###"
#define SCENE_HEADER_OBJ "--- Scene Objects -------"


static void default_config();


Scene::Scene()
: selected{nullptr}
,     name{"Untitled scene"}
{
    // temp ----
    Asagao::Application.atlas = std::make_unique<SpriteAtlas>("tiny-wonder-forest-summer.png", 16);
    Asagao::Application.shader->set_vec2("u_uv_frac", Asagao::Application.uv_fraction);
    Asagao::Application.shader->set_int("u_texture", Asagao::Application.atlas->texture->get_slot());
    Asagao::Renderer.set_background_color({114.0f/255.0f, 215.0f/255.0f, 59.0f/255.0f, 1.0f});
    Asagao::Application.animation_speed = 4.0f;

    for (u8 y = 0; y < 3; ++y)
    {
        for (u8 x = 0; x < 3; ++x)
        {
            objects.emplace_back
            (
                GameObject
                (
                    std::to_string(x) + "," + std::to_string(y),
                    v3
                    (
                        (x - 1) *  Asagao::Application.rect_size,
                        (y - 1) * -Asagao::Application.rect_size,
                        0.0f
                    ),
                    0.0f,
                    v3(1.0f),
                    0.0f,
                    true,
                    1,
                    {{
                        (5 + x) * Asagao::Application.uv_fraction.x,
                        (7 - y) * Asagao::Application.uv_fraction.y
                    }}
                )
            );
        }
    }

    objects.emplace_back
    (
        GameObject
        (
            "Lilypad",
            v3(0.0f),
            0.0f,
            v3(1.0f),
            0.0f,
            true,
            4,
            {
                {8 * Asagao::Application.uv_fraction.x, 4 * Asagao::Application.uv_fraction.y},
                {8 * Asagao::Application.uv_fraction.x, 5 * Asagao::Application.uv_fraction.y},
                {8 * Asagao::Application.uv_fraction.x, 6 * Asagao::Application.uv_fraction.y},
                {8 * Asagao::Application.uv_fraction.x, 7 * Asagao::Application.uv_fraction.y}
            }
        )
    );
    // ---------

    default_config();
}

// temp
// expecting that users did not "corrupt" the scene file
// or atleast kept the same format and logic as Scene::save
Scene::Scene
(const str& name)
: selected{nullptr}
,     name{name}
{
    // temp ----
    Asagao::Application.atlas = std::make_unique<SpriteAtlas>("kenney-pixel-platformer.png", 18);
    Asagao::Application.shader->set_vec2("u_uv_frac", Asagao::Application.uv_fraction);
    Asagao::Application.shader->set_int("u_texture", Asagao::Application.atlas->texture->get_slot());
    Asagao::Renderer.set_background_color({0.875f, 0.965f, 0.961f, 1.000f});
    Asagao::Application.animation_speed = 1.7f;
    // ---------

    std::ifstream file(SCENE_PATH + ("/" + name) + SCENE_EXT);

    if (!file.is_open())
    {
        LOG_ERROR("failed to open " + name);
        return;
    }

    str line, temp, num;

    while (std::getline(file, line))
    {
        if (line == SCENE_HEADER_OBJ)
        {
            std::getline(file, line);
            break;
        }
    }

    u64 help;
    f32 x, y;

    str  obj_name;
    v3   obj_position(0.0f), obj_scale(1.0f);
    f32  obj_depth, obj_rotation;
    bool obj_visible;
    u64  obj_sprite_count;

    std::vector<v2> obj_sprite_offsets;

    while (!file.eof())
    {
        // name
        std::getline(file, line);
        obj_name = line.substr(line.find(" ") + 1);

        // position
        std::getline(file, line);
        temp = line.substr(line.find(" ") + 1);
        help = temp.find(",");
        obj_position.x  = std::stof(temp.substr(0, help));
        obj_position.y  = std::stof(temp.substr(help + 1));
        obj_position   *= Asagao::Application.rect_size;

        // depth
        std::getline(file, line);
        obj_depth = std::stof(line.substr(line.find(" ") + 1));

        // scale
        std::getline(file, line);
        temp = line.substr(line.find(" ") + 1);
        help = temp.find(",");
        obj_scale.x = std::stof(temp.substr(0, help));
        obj_scale.y = std::stof(temp.substr(help + 1));

        // rotation
        std::getline(file, line);
        obj_rotation = std::stof(line.substr(line.find(" ") + 1));

        // visible
        std::getline(file, line);
        obj_visible = std::stoi(line.substr(line.find(" ") + 1));

        // sprite count
        std::getline(file, line);
        obj_sprite_count = std::stoull(line.substr(line.find(" ") + 1));

        // sprite offsets
        std::getline(file, line);
        std::istringstream iss(line.substr(line.find(" ") + 1));
        obj_sprite_offsets.clear();
        while (std::getline(iss, temp, ','))
        {
            x = std::stof(temp);
            std::getline(iss, temp, ',');
            y = std::stof(temp);

            obj_sprite_offsets.push_back
            (
                v2(x, y) * Asagao::Application.uv_fraction
            );
        }

        objects.emplace_back
        (
            obj_name,
            obj_position,
            obj_depth,
            obj_scale,
            obj_rotation,
            obj_visible,
            obj_sprite_count,
            obj_sprite_offsets
        );

        std::getline(file, line);
    }

    default_config();
}

void
Scene::save() const
{
    std::ofstream file(SCENE_PATH + ("/" + name) + SCENE_EXT);

    if (!file.is_open())
    {
        LOG_ERROR("failed to open " + name);
        return;
    }

    file << SCENE_HEADER_TOP << std::endl
         << std::endl
         << "version: " << SCENE_VER << std::endl
         << "name: " << name << std::endl
         << std::endl
         << SCENE_HEADER_OBJ << std::endl;

    u16 i;

    for (const GameObject& obj : objects)
    {
        file << std::endl
             << "name: " << obj.name
             << std::endl
             << "position: " << (obj.position.x / Asagao::Application.rect_size)
                             << ","
                             << (obj.position.y / Asagao::Application.rect_size)
             << std::endl
             << "depth: " << obj.depth
             << std::endl
             << "scale: " << obj.scale.x
                          << ","
                          << obj.scale.y
             << std::endl
             << "rotation: " << obj.rotation
             << std::endl
             << "visible: " << obj.visible
             << std::endl
             << "sprite_count: " << obj.sprite_count
             << std::endl
             << "sprite_offsets: ";

        i = 0;

        for (const v2& ofs : obj.sprite_offsets)
        {
            if (i++)
                file << ",";

            file << ofs.x / Asagao::Application.uv_fraction.x << ","
                 << ofs.y / Asagao::Application.uv_fraction.y;
        }

        file << std::endl;
    }

    file.close();
}

void
Scene::unload()
{
    Asagao::Interface.current_view = STARTUP_VIEW;

    Asagao::Application.scene = nullptr;
}


static void
default_config()
{
    Asagao::Renderer.zoom = 1.0f;

    Asagao::Camera.set_position({0.0f, 0.0f, 0.0f});

    Asagao::Interface.current_view = SCENE_VIEW;
}
