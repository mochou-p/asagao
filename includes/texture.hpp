// asagao/includes/texture.hpp


#pragma once


class Texture
{
public:
    Texture(const str& filepath, bool flip_y = true);
    ~Texture();

    inline const v2& get_size() const { return m_size; }

    void bind() const;
private:
    v2  m_size;
    u32 m_id;
};
