// asagao/source/sprite_atlas.cpp


#include "sprite_atlas.hpp"

#define ATLAS_PATH "atlases/"

SpriteAtlas::SpriteAtlas
(
 const std::string& filepath,
       unsigned int sprite_size
)
: sprite_size{sprite_size, sprite_size, 0.0f}
{
    texture = std::make_unique<Texture>(ATLAS_PATH + filepath);

    sprite_uv_frac = (float) sprite_size / texture->get_size();
}
