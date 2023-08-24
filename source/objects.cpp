// asagao/source/objects.cpp


#include "objects.hpp"

VertexBuffer::VertexBuffer(const void*      data,
                                 GLsizeiptr size)
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

IndexBuffer::IndexBuffer(const GLuint* data,
                               GLuint  count)
: m_count(count)
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data,
        GL_STATIC_DRAW);
}

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

static GLboolean
get_type_normalisation(GLenum type)
{
    switch (type)
    {
        case GL_FLOAT: return GL_FALSE;
    }

    quit("unsupported VertexAttribute type");
    return false;
}

void
VertexBufferLayout::push(GLuint count,
                         GLenum type)
{
    m_attributes.push_back({count, type, get_type_normalisation(type)});
    m_stride += count * VertexAttribute::get_size_of_type(type);
}
