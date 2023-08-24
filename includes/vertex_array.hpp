// asagao/includes/vertex_array.hpp


#pragma once
#ifndef __vertex_array_hpp_
#define __vertex_array_hpp_

#include "glad/glad.h"
#include "vertex_buffer.hpp"
#include "vertex_buffer_layout.hpp"

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    void add_vertex_buffer(const VertexBuffer& vb,
        const VertexBufferLayout& layout) const;
private:
    GLuint m_id;
};

#endif  // __vertex_array_hpp_
