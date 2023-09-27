// asagao/includes/texture.hpp


#pragma once


class Texture
{
public:
    Texture(const str& filepath, bool flip_y = true);
    ~Texture();

    static inline u32 count = 0;

    inline       u32 get_slot() const { return m_slot; }
    inline const v2& get_size() const { return m_size; }
private:
    u32 m_slot;
    v2  m_size;
    u32 m_id;
};
