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
    VertexArray()  { glGenVertexArrays(1, &m_id); }
    ~VertexArray() { glDeleteVertexArrays(1, &m_id); }

    void bind() { glBindVertexArray(m_id); }
    void add_vertex_buffer(VertexBuffer& vb, VertexBufferLayout& layout);
private:
    GLuint m_id;
};

#endif  // __vertex_array_hpp_
