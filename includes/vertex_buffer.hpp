// asagao/includes/vertex_buffer.hpp


#pragma once
#ifndef __vertex_buffer_hpp_
#define __vertex_buffer_hpp_

#include "glad/glad.h"

class VertexBuffer
{
public:
    VertexBuffer(const void* data, GLsizeiptr size);
    ~VertexBuffer();

    void bind() const;
private:
    GLuint m_id;
};

#endif  // __vertex_buffer_hpp_
