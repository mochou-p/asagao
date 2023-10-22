// asagao/includes/game_object.hpp


#pragma once


struct GameObject
{
    str  name;
    v3   position;
    f32  depth;
    v3   scale;
    f32  rotation;
    bool visible;
    u64  sprite_count;

    std::vector<v2> sprite_offsets;

    inline const v2& get_uv(const u32 frame) const
    { return sprite_offsets[frame % sprite_count]; }

    GameObject
    (
     const str& name,
     const v3&  position,
           f32  depth,
     const v3&  scale,
           f32  rotation,
           bool visible,
           u64  sprite_count,

     const std::vector<v2>& sprite_offsets
    )
    :           name{name}
    ,       position{position}
    ,          depth{depth}
    ,          scale{scale}
    ,       rotation{rotation}
    ,        visible{visible}
    ,   sprite_count{sprite_count}
    , sprite_offsets{sprite_offsets}
    {}

    static str
    get_new_number()
    {
        static u16 i = 0;

        return std::to_string(++i);
    }

    void move(const v2& offset) { position.x += offset.x; position.y += offset.y; }
};
