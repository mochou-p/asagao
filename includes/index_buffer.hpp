// asagao/includes/index_buffer.hpp


#pragma once

class Rect;

class IndexBuffer
{
public:
    IndexBuffer(const Rect& quad);
    ~IndexBuffer();

    inline unsigned int get_count() const { return m_count; }
    void bind() const;
private:
    unsigned int m_id;
    unsigned int m_count;
};
