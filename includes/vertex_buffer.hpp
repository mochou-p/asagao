// asagao/includes/vertex_buffer.hpp


#pragma once
#ifndef __vertex_buffer_hpp_
#define __vertex_buffer_hpp_

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

#endif  // __vertex_buffer_hpp_
