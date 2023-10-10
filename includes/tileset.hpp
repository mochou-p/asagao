// asagao/includes/tileset.hpp


#pragma once


#include "texture.hpp"


class TileSet
{
public:
    TileSet(const str& filepath, u32 tile_size);

    std::unique_ptr<Texture> texture;
};
