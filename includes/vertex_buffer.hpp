// asagao/includes/vertex_buffer.hpp


#pragma once
#ifndef __vertex_buffer_hpp_
#define __vertex_buffer_hpp_

#include "glad/glad.h"

class VertexBuffer
{
public:
    VertexBuffer(const void* data, GLsizeiptr size);
    ~VertexBuffer() { glDeleteBuffers(1, &m_id); }

    void bind() { glBindBuffer(GL_ARRAY_BUFFER, m_id); }
private:
    GLuint m_id;
};

#endif  // __vertex_buffer_hpp_
