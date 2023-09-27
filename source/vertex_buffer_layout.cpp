// asagao/source/vertex_buffer_layout.cpp


#include "stdafx.h"

#include "vertex_buffer_layout.hpp"
#include "log.hpp"


static bool get_type_normalisation(u32 type);


VertexBufferLayout::VertexBufferLayout()
: m_stride(0)
{}

void
VertexBufferLayout::push
(u32 count, u32 type)
{
    m_attributes.push_back({count, type, get_type_normalisation(type)});

    m_stride += count * VertexAttribute::get_size_of_type(type);
}


static bool
get_type_normalisation
(u32 type)
{
    switch (type)
    {
        case GL_FLOAT:
            return GL_FALSE;
        default:
            LOG_WARN("unsupported type");
            break;
    }

    return false;
}
