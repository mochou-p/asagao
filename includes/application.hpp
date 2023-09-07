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
    std::string name;
    glm::vec3   position;
    float       depth;
    glm::vec3   scale;
    float       rotation;
    bool        visible;

    std::vector<glm::vec2> sprite_offsets;
    long long unsigned int sprite_count;
};

class Application
{
public:
    Application() {};

    void run();

    static inline std::deque<GameObject> objects;
    static inline GameObject*            selected_obj = nullptr;

    static inline bool view_changed = true;

    static inline glm::vec2 aspect;
    static inline glm::vec3 camera = {0.0f, 0.0f, 0.0f};

    static inline       float     animation_speed =   1.7f;
    static inline const float     rect_size       = 100.0f;
    static inline       glm::vec2 uv_frac;
};

#endif  // __application_hpp_
