// asagao/includes/sprite_atlas.hpp


#pragma once

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
