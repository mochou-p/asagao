// asagao/includes/vertex_buffer.hpp


#pragma once

#include "types.hpp"

class Rect;

class VertexBuffer
{
public:
    VertexBuffer(const Rect& quad);
    ~VertexBuffer();

    void bind() const;
private:
    u32 m_id;
};
