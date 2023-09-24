// asagao/includes/texture.hpp


#pragma once

#include "glm.hpp"

#include <string>

class Texture
{
public:
    Texture(const std::string& filepath, bool flip_y = true);
    ~Texture();

    static inline unsigned int count = 0;

    inline       unsigned int get_slot() const { return m_slot; }
    inline const glm::vec2&   get_size() const { return m_size; }
private:
    unsigned int m_slot;
    glm::vec2    m_size;
    unsigned int m_id;
};
