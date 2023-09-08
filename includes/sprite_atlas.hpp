// asagao/includes/sprite_atlas.hpp


#pragma once
#ifndef __sprite_atlas_hpp_
#define __sprite_atlas_hpp_

#include <string>
#include <memory>
#include "texture.hpp"
#include "glm.hpp"

class SpriteAtlas
{
public:
    SpriteAtlas(const std::string& filepath, unsigned int sprite_size);
    ~SpriteAtlas() {}

    std::unique_ptr<Texture> texture;
};

#endif  // __sprite_atlas_hpp_
