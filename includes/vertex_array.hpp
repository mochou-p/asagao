// asagao/includes/vertex_array.hpp


#pragma once

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
    unsigned int m_id;
};
