// asagao/includes/texture.hpp


#pragma once
#ifndef __texture_hpp_
#define __texture_hpp_

#include <string>
#include "glad/glad.h"

class Texture
{
public:
    Texture(const std::string& filepath);
    ~Texture();

    static inline GLuint count = 0;

    inline GLuint get_slot() const { return m_slot; }
private:
    GLuint m_slot;
    GLuint m_id;
};

#endif  // __texture_hpp_
