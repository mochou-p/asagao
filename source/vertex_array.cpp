// asagao/source/vertex_array.cpp


#include "vertex_array.hpp"

void
VertexArray::add_vertex_buffer([[maybe_unused]] VertexBuffer&       vb,
                                                VertexBufferLayout& layout)
{
    bind();

    const auto& attributes = layout.get_attributes();
    GLuint pointer = 0;

    for (GLuint i = 0; i < attributes.size(); ++i)
    {
        const auto& attrib = attributes[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, attrib.count, attrib.type, attrib.normalized,
            layout.get_stride(), (const void*) (unsigned long long) pointer);
        pointer +=
            attrib.count * VertexAttribute::get_size_of_type(attrib.type);
    }
}
