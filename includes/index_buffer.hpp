// asagao/includes/index_buffer.hpp


#pragma once
#ifndef __index_buffer_hpp_
#define __index_buffer_hpp_

#include "glad/glad.h"

class IndexBuffer
{
public:
    IndexBuffer(const GLuint* data, GLuint count);
    ~IndexBuffer();

    void bind() const;
    inline GLuint get_count() const { return m_count; }
private:
    GLuint m_id;
    GLuint m_count;
};

#endif  // __index_buffer_hpp_
