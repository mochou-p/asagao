// asagao/includes/vertex_buffer_layout.hpp


#pragma once
#ifndef __vertex_buffer_layout_hpp_
#define __vertex_buffer_layout_hpp_

#include <vector>
#include "log.hpp"
#include "glad/glad.h"

struct VertexAttribute
{
    unsigned int count;
    unsigned int type;
    bool         normalized;

    static unsigned int
    get_size_of_type(unsigned int type)
    {
        switch (type)
        {
            case GL_FLOAT:
                return 4;
            default:
                LOG_WARN("unsupported type");
                break;
        }

        return 0;
    }
};

class VertexBufferLayout
{
public:
    VertexBufferLayout();

    void push(unsigned int count, unsigned int type);
    inline unsigned int get_stride() const { return m_stride; }
    inline const std::vector<VertexAttribute>& get_attributes() const
    { return m_attributes; }
private:
    std::vector<VertexAttribute> m_attributes;
    unsigned int m_stride;
};

#endif  // __vertex_buffer_layout_hpp_
