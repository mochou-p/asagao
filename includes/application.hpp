// asagao/includes/application.hpp


#pragma once

#include "scene.hpp"

#include "glm.hpp"

#include <memory>

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

        const float rect_size       = 100.0f;
        float       animation_speed =   1.0f;
        glm::vec2   uv_fraction;

        std::unique_ptr<Scene> scene;
    };
}  // Asagao::
