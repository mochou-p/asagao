// asagao/includes/tileset.hpp


#pragma once


#include "texture.hpp"


class TileSet
{
public:
    TileSet(const str& filepath, u16 tile_size);

    std::unique_ptr<Texture> texture;

    std::vector<GameObject>   game_objects;
    std::vector<TileSetLayer> tile_set_layers;

    str name;
    u16 tile_size;
};
