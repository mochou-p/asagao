// asagao/includes/game_object.hpp


#pragma once


struct Animation
{
    str             name           = "Idle";
    u16             sprite_count   = 1;
    std::vector<v2> sprite_offsets = {{12, 0}};
};

struct GameObject
{
    str  name     = "GameObject " + get_new_number();
    v3   position = {0.0f, 0.0f, 0.0f};
    v3   scale    = {1.0f, 1.0f, 1.0f};
    f32  rotation = 0.0f;
    f32  depth    = 0.0f;
    bool visible  = true;

    std::vector<Animation> animations = {Animation()};
    u16 current_animation             = 0;
    f32 animation_speed               = 1.0f;

    inline const v2&
    get_uv(const u32 frame) const
    {
        const auto& anim = animations[current_animation];

        return anim.sprite_offsets[(u32) (frame * animation_speed) % anim.sprite_count];
    }

    static str
    get_new_number()
    {
        static u16 i = 0;

        return std::to_string(++i);
    }

    void
    move(const v2& offset)
    {
        position.x += offset.x;
        position.y += offset.y;
    }
};
