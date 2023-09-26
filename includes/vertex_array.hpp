// asagao/includes/vertex_array.hpp


#pragma once

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
    unsigned int m_id;
};
