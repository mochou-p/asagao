// asagao/source/index_buffer.cpp


#include "index_buffer.hpp"
#include "rect.hpp"

#include "glad/glad.h"

IndexBuffer::IndexBuffer
(const Rect& quad)
: m_count(quad.get_indices_count())
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(unsigned int), quad.get_indices(), GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer
()
{
    glDeleteBuffers(1, &m_id);
}

void
IndexBuffer::bind
() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}
