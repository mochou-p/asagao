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

    static GameObject&
    find(const str& tag)
    {
        auto val = hashed_objects.at(tag);

        return assets.tile_sets[val[0]].game_objects[val[1]];
    }

    void unload();
    void draw() const;

    static inline std::unordered_map<str, std::array<int, 2>> hashed_objects;
    static inline Assets assets;

    str name;
};
