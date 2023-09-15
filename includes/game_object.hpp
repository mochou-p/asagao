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
    size_t      sprite_count;

    std::vector<glm::vec2> sprite_offsets;

    inline const glm::vec2& get_uv(const unsigned int animation_time) const
    { return sprite_offsets[animation_time % sprite_count]; }

    GameObject
    (
     const std::string& name,
     const glm::vec3&   position,
           float        depth,
     const glm::vec3&   scale,
           float        rotation,
           bool         visible,
           size_t       sprite_count,

     const std::vector<glm::vec2>& sprite_offsets
    )
    : name{name}
    , position{position}
    , depth{depth}
    , scale{scale}
    , rotation{rotation}
    , visible{visible}
    , sprite_count{sprite_count}
    , sprite_offsets{sprite_offsets}
    {}
};

#endif  // __game_object_hpp_
