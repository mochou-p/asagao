// asagao/includes/vertex_buffer.hpp


#pragma once

class Rect;

class VertexBuffer
{
public:
    VertexBuffer(const Rect& quad);
    ~VertexBuffer();

    void bind() const;
private:
    unsigned int m_id;
};
