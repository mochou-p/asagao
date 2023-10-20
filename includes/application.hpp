// asagao/includes/application.hpp


#pragma once


#include "tileset.hpp"
#include "shader.hpp"
#include "scene.hpp"


namespace Asagao
{
    class Application
    {
    SINGLETON(Application)

    public:
        void run(const str& argv_scene = "");

        const f32 rect_size = 100.0f;
        f32  animation_speed = 1.0f;
        bool is_painting_tiles;

        std::unique_ptr<TileSet> tileset;
        std::unique_ptr<Shader>  shader;
        std::unique_ptr<Scene>   scene;
    };
}  // Asagao::
