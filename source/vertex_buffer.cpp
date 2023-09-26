// asagao/source/vertex_buffer.cpp


#include "vertex_buffer.hpp"
#include "rect.hpp"

#include "glad/glad.h"

VertexBuffer::VertexBuffer
(const Rect& quad)
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, quad.get_vertices_size(), quad.get_vertices(), GL_STATIC_DRAW);
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
