// asagao/source/tileset.cpp


#include "stdafx.h"

#include "asagao.hpp"

#include "tileset.hpp"
#include "application.hpp"


#define TILESET_PATH "tilesets/"


TileSet::TileSet
(const str& filepath, u16 tile_size)
:      name{filepath}
, tile_size{tile_size}
{
    texture = std::make_unique<Texture>(TILESET_PATH + filepath);

    Asagao::Application.uv_fraction = (f32) tile_size / texture->get_size();
}
