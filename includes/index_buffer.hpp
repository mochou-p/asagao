// asagao/includes/index_buffer.hpp


#pragma once

class Rect;

class IndexBuffer
{
public:
    IndexBuffer(const Rect& quad);
    ~IndexBuffer();

    void bind() const;
    inline unsigned int get_count() const { return m_count; }
private:
    unsigned int m_id;
    unsigned int m_count;
};
