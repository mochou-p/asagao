// asagao/includes/tileset_layer.hpp


#pragma once


struct pair_hash
{
    template<class T1, class T2>
    u64 operator()
    (const std::pair<T1, T2>& p) const
    {
        return std::hash<T1>{}(p.first) ^ std::hash<T2>{}(p.second);  
    }
};


using TileUV  = v2;
using TilePos = std::pair<i32, i32>;
using TileMap = std::unordered_map<TilePos, TileUV, pair_hash>;


class TileSetLayer
{
public:
    TileSetLayer(const str& name);

    static str get_new_number();

    void paint(const v2& tile);
    void draw() const;

    str name;
private:
    TileUV get_uv(const v2& tile) const;

    TileMap tiles;
};
