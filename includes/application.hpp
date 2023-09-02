// asagao/includes/application.hpp


#pragma once
#ifndef __application_hpp_
#define __application_hpp_

#include <string>
#include <vector>
#include <initializer_list>
#include <deque>
#include <memory>
#include "glm.hpp"
#include "texture.hpp"
#include "renderer.hpp"

struct GameObject
{
    std::string    name;
    glm::vec3      position;
    float          depth;
    glm::vec3      scale;
    float          rotation;
    bool           visible;
    unsigned short texture_count;

    std::vector<std::unique_ptr<Texture>> textures;

    GameObject
    (
     const std::string&                       name,
     const glm::vec2&                         position,
           std::initializer_list<std::string> texture_filepaths,
     const glm::vec2&                         size     = {1.0f, 1.0f},
           float                              parallax = 0.0f,
           float                              rotation = 0.0f
    )
    :     name{name}
    , position{position.x, position.y, 0.0f}
    ,    depth{parallax}
    ,    scale{size.x, size.y, 1.0f}
    , rotation{rotation}
    ,  visible{true}
    {
        for (const std::string& p : texture_filepaths)
            textures.push_back(std::make_unique<Texture>(p));

        texture_count = textures.size();
    }
};

class Application
{
public:
    Application() {};

    static void new_object();

    void run();

    static inline std::deque<GameObject> objects;
    static inline GameObject*            selected_obj = nullptr;

    static inline bool view_changed = true;

    static inline glm::vec2 aspect;
    static inline glm::vec3 camera = {0.0f, 0.0f, 0.0f};

    static inline float animation_speed = 7.0f;
private:
    void load_demo_scene(unsigned int id, const Renderer& renderer);
};

#endif  // __application_hpp_
