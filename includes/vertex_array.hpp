// asagao/includes/vertex_array.hpp


#pragma once

#include "types.hpp"

class VertexBuffer;
class VertexBufferLayout;

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    void add_vertex_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout) const;
private:
    u32 m_id;
};
