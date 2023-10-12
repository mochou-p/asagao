// asagao/includes/scene.hpp


#pragma once


#include "game_object.hpp"
#include "tileset_layer.hpp"


class Scene
{
public:
    Scene();
    Scene(const str& filepath);

    void save() const;
    void unload();
    void draw() const;

    std::vector<GameObject>   objects;
    std::vector<TileSetLayer> tilemaps;

    void* selected;
    str   name;
    u16   current_tilemap;
};
