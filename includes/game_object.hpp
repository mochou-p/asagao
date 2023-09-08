// asagao/includes/game_object.hpp


#pragma once
#ifndef __game_object_hpp_
#define __game_object_hpp_

#include <string>
#include <vector>
#include "glm.hpp"

struct GameObject
{
    std::string name;
    glm::vec3   position;
    float       depth;
    glm::vec3   scale;
    float       rotation;
    bool        visible;

    long long unsigned int sprite_count;
    std::vector<glm::vec2> sprite_offsets;
};

#endif  // __game_object_hpp_
