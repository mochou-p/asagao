// asagao/includes/application.hpp


#pragma once


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
        f32 animation_speed = 1.0f;
        v2  uv_fraction;

        std::unique_ptr<Shader> shader;
        std::unique_ptr<Scene>  scene;
    };
}  // Asagao::
