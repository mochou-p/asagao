// asagao/includes/index_buffer.hpp


#pragma once


class IndexBuffer
{
public:
    IndexBuffer(const Rect& quad);
    ~IndexBuffer();

    inline u32 get_count() const { return m_count; }
private:
    u32 m_id;
    u32 m_count;
};
