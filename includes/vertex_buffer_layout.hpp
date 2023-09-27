// asagao/includes/vertex_buffer_layout.hpp


#pragma once


#include "log.hpp"


struct VertexAttribute
{
    u32  count;
    u32  type;
    bool normalized;

    static u32
    get_size_of_type
    (u32 type)
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

    inline u32 get_stride() const { return m_stride; }
    inline const std::vector<VertexAttribute>& get_attributes() const
    { return m_attributes; }
    void push(u32 count, u32 type);
private:
    std::vector<VertexAttribute> m_attributes;
    u32 m_stride;
};
