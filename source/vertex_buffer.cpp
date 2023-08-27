// asagao/source/vertex_buffer.cpp


#include "vertex_buffer.hpp"
#include "glad/glad.h"

VertexBuffer::VertexBuffer
(
 const void*  data,
       size_t size
)
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_id);
}

void
VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}
