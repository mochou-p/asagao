// asagao/includes/vertex_buffer.hpp


#pragma once

#include <cstddef>
#include "rect.hpp"

class VertexBuffer
{
public:
    VertexBuffer(const Rect& quad);
    ~VertexBuffer();

    void bind() const;
private:
    unsigned int m_id;
};
