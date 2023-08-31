// asagao/includes/application.hpp


#pragma once
#ifndef __application_hpp_
#define __application_hpp_

#include <string>
#include <deque>
#include <memory>
#include "glm.hpp"
#include "texture.hpp"

struct GameObject
{
    std::string name;
    glm::vec3   position;
    float       depth;
    glm::vec3   scale;
    float       rotation;
    bool        visible;

    std::unique_ptr<Texture> tex;

    GameObject
    (
     const std::string& name,
     const glm::vec2&   position,
     const std::string& texture_filepath,
     const glm::vec2&   size     = {1.0f, 1.0f},
           float        parallax = 0.0f,
           float        rotation = 0.0f
    )
    :     name{name}
    , position{position.x, position.y, 0.0f}
    ,    depth{parallax}
    ,    scale{size.x, size.y, 1.0f}
    , rotation{rotation}
    ,  visible{true}
    {
        tex = std::make_unique<Texture>(texture_filepath);
    }
};

class Application
{
public:
    Application() {};

    static void new_object();

    void run() const;

    static inline std::deque<GameObject> objects;
    static inline GameObject*            selected_obj = nullptr;

    static inline bool view_changed = true;

    static inline glm::vec2 aspect;
    static inline glm::vec3 camera = {0.0f, 0.0f, 0.0f};
};

#endif  // __application_hpp_
