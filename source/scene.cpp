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
, current_tilemap{0}
,            name{"Untitled scene"}
{
    Asagao::Window.set_title(name);

    assets.tile_sets.emplace_back(TileSet("default-tileset.png", 8));

    default_config();
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
    // cause binding a tex is expensive
    static bool is_tex_bound;

    // Benchmark _("Scene render");

    // it could be a TileSet public function
    for (const auto& ts : assets.tile_sets)
    {
        for (const auto& tm : ts.tile_set_layers)
        {
            if (!is_tex_bound)
            {
                ts.texture->bind();
                // and change uv fraction and do it on gpu,
                // so we can keep GO numbers nice and do fractions based on currently bound tileset

                is_tex_bound ^= 1;
            }

            tm.draw();
        }

        for (const auto& go : ts.game_objects)
        {
            if (go.visible)
            {
                if (!is_tex_bound)
                {
                    ts.texture->bind();
                    // ...

                    is_tex_bound ^= 1;
                }

                Asagao::Renderer.draw(go);
            }
        }

        is_tex_bound = false;
    }
}


static void
default_config()
{
    Asagao::Renderer.zoom = 1.0f;
    Asagao::Application.animation_speed = 1.0f;
    Asagao::Camera.set_position({0.0f, 0.0f, 0.0f});

    Asagao::Interface.current_view = SCENE_VIEW;
}
