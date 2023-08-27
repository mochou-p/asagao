// asagao/includes/texture.hpp


#pragma once
#ifndef __texture_hpp_
#define __texture_hpp_

#include <string>

class Texture
{
public:
    Texture(const std::string& filepath);
    ~Texture();

    static inline unsigned int count = 0;

    inline unsigned int get_slot() const { return m_slot; }
private:
    unsigned int m_slot;
    unsigned int m_id;
};

#endif  // __texture_hpp_
