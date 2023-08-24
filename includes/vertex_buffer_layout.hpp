// asagao/includes/vertex_buffer_layout.hpp


#pragma once
#ifndef __vertex_buffer_layout_hpp_
#define __vertex_buffer_layout_hpp_

#include <vector>
#include "glad/glad.h"
#include "utils.hpp"

struct VertexAttribute
{
    GLuint    count;
    GLenum    type;
    GLboolean normalized;

    static GLuint
    get_size_of_type(GLenum type)
    {
        switch (type)
        {
            case GL_FLOAT: return 4;
        }

        quit("unsupported VertexAttribute type");
        return 0;
    }
};

class VertexBufferLayout
{
public:
    VertexBufferLayout()
    : m_stride{0}
    {}

    void push(GLuint count, GLenum type);
    GLuint get_stride() { return m_stride; }
    const std::vector<VertexAttribute>& get_attributes()
    { return m_attributes; }
private:
    std::vector<VertexAttribute> m_attributes;
    GLuint m_stride;
};

#endif  // __vertex_buffer_layout_hpp_
