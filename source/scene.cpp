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
:        selected{nullptr}
,            name{"Untitled scene"}
, current_tilemap{0}
{
    // temp ----
    Asagao::Application.tileset = std::make_unique<TileSet>("test-ruled-tiles.png", 8);
    Asagao::Application.shader->set_vec2("u_uv_frac", Asagao::Application.uv_fraction);
    Asagao::Application.shader->set_int("u_texture", Asagao::Application.tileset->texture->get_slot());
    Asagao::Renderer.set_background_color({195.0f / 255.0f, 223.0f / 255.0f, 224.0f / 255.0f, 1.0f});
    Asagao::Application.animation_speed = 1.0f;
    Asagao::Window.set_title(name);

    default_config();
}

// temp
// expecting that users did not "corrupt" the scene file
// or atleast kept the same format and logic as Scene::save
Scene::Scene
(const str& name)
:        selected{nullptr}
,            name{name}
, current_tilemap{0}
{
    // temp ----
    Asagao::Application.tileset = std::make_unique<TileSet>("kenney-pixel-platformer.png", 18);
    Asagao::Application.shader->set_vec2("u_uv_frac", Asagao::Application.uv_fraction);
    Asagao::Application.shader->set_int("u_texture", Asagao::Application.tileset->texture->get_slot());
    Asagao::Renderer.set_background_color({0.875f, 0.965f, 0.961f, 1.000f});
    Asagao::Application.animation_speed = 1.7f;
    Asagao::Window.set_title(name);


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

        objects.game_objects.emplace_back
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

    for (const auto& obj : objects.game_objects)
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

        for (const auto& ofs : obj.sprite_offsets)
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
    Asagao::Window.set_title("");

    Asagao::Application.scene = nullptr;
}

void
Scene::draw() const
{
    // Benchmark _("Scene render");

    for (const auto& tm : objects.tile_set_layers)
        tm.draw();

    for (const auto& obj : objects.game_objects)
    {
        if (obj.visible)
            Asagao::Renderer.draw(obj);
    }
}


static void
default_config()
{
    Asagao::Renderer.zoom = 1.0f;

    Asagao::Camera.set_position({0.0f, 0.0f, 0.0f});

    Asagao::Interface.current_view = SCENE_VIEW;
}
