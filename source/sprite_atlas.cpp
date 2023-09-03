// asagao/source/sprite_atlas.cpp


#include "sprite_atlas.hpp"

SpriteAtlas::SpriteAtlas
(
 const std::string& filepath,
       unsigned int sprite_size
)
: sprite_size{sprite_size, sprite_size, 0.0f}
{
    texture = std::make_unique<Texture>(filepath);

    sprite_uv_frac = (float) sprite_size / texture->get_size();
}
