// asagao/includes/sprite_atlas.hpp


#pragma once

#include "texture.hpp"

#include <memory>

class SpriteAtlas
{
public:
    SpriteAtlas(const str& filepath, u32 sprite_size);

    std::unique_ptr<Texture> texture;
};
