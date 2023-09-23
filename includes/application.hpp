// asagao/includes/application.hpp


#pragma once
#ifndef __application_hpp_
#define __application_hpp_

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
        float       animation_speed =   1.7f;
        glm::vec2   uv_fraction;

        std::unique_ptr<Scene> scene;
    };
}

#endif  // __application_hpp_
