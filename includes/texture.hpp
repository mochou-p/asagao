// asagao/includes/texture.hpp


#pragma once
#ifndef __texture_hpp_
#define __texture_hpp_

#include <string>
#include "glad/glad.h"

class Texture
{
public:
    Texture(const std::string&);
    ~Texture() { glDeleteTextures(1, &m_id); }

    static inline unsigned int count = 0;

    GLuint get_order() { return m_order; }
private:
    GLuint m_order;
    GLuint m_id;
};

#endif  // __texture_hpp_
