// asagao/includes/sprite_atlas.hpp


#pragma once

#include "texture.hpp"

#include "glm.hpp"

#include <memory>
#include <string>

class SpriteAtlas
{
public:
    SpriteAtlas(const std::string& filepath, unsigned int sprite_size);

    std::unique_ptr<Texture> texture;
};
