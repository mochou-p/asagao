// asagao/includes/vertex_buffer.hpp


#pragma once


class VertexBuffer
{
public:
    VertexBuffer(const Rect& quad);
    ~VertexBuffer();
private:
    u32 m_id;
};
