// asagao/includes/index_buffer.hpp


#pragma once
#ifndef __index_buffer_hpp_
#define __index_buffer_hpp_

#include "glad/glad.h"

class IndexBuffer
{
public:
    IndexBuffer(const GLuint* data, GLuint count);
    ~IndexBuffer() { glDeleteBuffers(1, &m_id); }

    void bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id); }
    GLuint get_count() { return m_count; }
private:
    GLuint m_id;
    GLuint m_count;
};

#endif  // __index_buffer_hpp_
