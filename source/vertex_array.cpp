// asagao/source/vertex_array.cpp


#include "stdafx.h"

#include "vertex_array.hpp"
#include "vertex_buffer.hpp"
#include "vertex_buffer_layout.hpp"


VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_id);

    glBindVertexArray(m_id);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_id);
}

void
VertexArray::add_vertex_buffer
(const VertexBufferLayout& layout) const
{
    const auto& attributes = layout.get_attributes();
    const auto  stride     = layout.get_stride();

    u64 offset = 0;
    u8  i      = 0;

    for (const auto& va : attributes)
    {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, va.count, va.type, va.normalized, stride, (const void*) offset);

        offset += va.count * VertexAttribute::get_size_of_type(va.type);

        ++i;
    }
}
