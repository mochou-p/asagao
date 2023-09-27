// asagao/includes/application.hpp


#pragma once


#include "scene.hpp"


namespace Asagao
{
    class Application
    {
    public:
        static Application& get_instance()
        {
            static Application instance;

            return instance;
        }
    private:
        Application() {}

        Application           (const Application&) = delete;
        Application& operator=(const Application&) = delete;


    public:
        void run() const;

        const f32 rect_size = 100.0f;
        f32 animation_speed = 1.0f;
        v2  uv_fraction;

        std::unique_ptr<Scene> scene;
    };
}  // Asagao::
