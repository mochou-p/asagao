// asagao/source/vertex_array.cpp


#include "vertex_array.hpp"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_id);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_id);
}

void
VertexArray::bind() const
{
    glBindVertexArray(m_id);
}

void
VertexArray::add_vertex_buffer
(
 const VertexBuffer&       vb,
 const VertexBufferLayout& layout
) const
{
    bind();
    vb.bind();

    const auto& attributes = layout.get_attributes();
    unsigned int  offset = 0;
    unsigned char i = 0;

    for (const VertexAttribute& va : attributes)
    {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer
        (
            i,
            va.count, va.type, va.normalized,
            layout.get_stride(),
            (const void*) (size_t) offset
        );

        offset += va.count * VertexAttribute::get_size_of_type(va.type);

        ++i;
    }
}
