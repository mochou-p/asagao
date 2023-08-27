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
    unsigned int offset = 0;

    for (unsigned int i = 0; i < attributes.size(); ++i)
    {
        const auto& attrib = attributes[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, attrib.count, attrib.type, attrib.normalized,
            layout.get_stride(), (const void*) (size_t) offset);
        offset +=
            attrib.count * VertexAttribute::get_size_of_type(attrib.type);
    }
}
