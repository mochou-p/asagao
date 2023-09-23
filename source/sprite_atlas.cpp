// asagao/source/sprite_atlas.cpp


#include "asagao.hpp"

#include "sprite_atlas.hpp"
#include "application.hpp"

#define ATLAS_PATH "atlases/"

SpriteAtlas::SpriteAtlas
(
 const std::string& filepath,
       unsigned int sprite_size
)
{
    texture = std::make_unique<Texture>(ATLAS_PATH + filepath);

    Asagao::Application.uv_fraction = (float) sprite_size / texture->get_size();
}
