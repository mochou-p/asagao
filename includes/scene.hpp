// asagao/includes/scene.hpp


#pragma once


#include "game_object.hpp"
#include "tileset_layer.hpp"


#define DEFAULT_TILESET 0


enum class AsagaoType
{
    // Objects
    GameObject,
    TileSetLayer,

    // Assets
    TileSet
};


struct Assets
{
    std::vector<TileSet> tile_sets;
};


class Scene
{
public:
    Scene();

    void unload();
    void draw() const;

    Assets  assets;

    void*      selected;
    AsagaoType selected_type;

    str name;
};
