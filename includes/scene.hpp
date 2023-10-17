// asagao/includes/scene.hpp


#pragma once


#include "game_object.hpp"
#include "tileset_layer.hpp"


struct Objects
{
    std::vector<GameObject>   game_objects;
    std::vector<TileSetLayer> tile_set_layers;
};

struct Assets
{
    std::vector<TileSet> tile_sets;
};


class Scene
{
public:
    Scene();
    Scene(const str& filepath);

    void save() const;
    void unload();
    void draw() const;

    Objects objects;
    Assets  assets;

    void* selected;
    str   name;
    u16   current_tilemap;
};
