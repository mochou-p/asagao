// asagao/includes/vertex_buffer_layout.hpp


#pragma once

#include "log.hpp"

#include "glad/glad.h"

#include <vector>

struct VertexAttribute
{
    unsigned int count;
    unsigned int type;
    bool         normalized;

    static unsigned int
    get_size_of_type
    (unsigned int type)
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

    inline unsigned int get_stride() const { return m_stride; }
    inline const std::vector<VertexAttribute>& get_attributes() const
    { return m_attributes; }
    void push(unsigned int count, unsigned int type);
private:
    std::vector<VertexAttribute> m_attributes;
    unsigned int m_stride;
};
