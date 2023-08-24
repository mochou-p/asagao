// asagao/source/vertex_buffer.cpp


#include "vertex_buffer.hpp"

VertexBuffer::VertexBuffer(const void*      data,
                                 GLsizeiptr size)
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}