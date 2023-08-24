// asagao/source/vertex_buffer_layout.cpp


#include "vertex_buffer_layout.hpp"

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
