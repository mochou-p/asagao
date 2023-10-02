// asagao/source/index_buffer.cpp


#include "stdafx.h"

#include "index_buffer.hpp"
#include "rect.hpp"


IndexBuffer::IndexBuffer
(const Rect& quad)
: m_count(quad.get_indices_count())
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(u32), quad.get_indices(), GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_id);
}
