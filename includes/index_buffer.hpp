// asagao/includes/index_buffer.hpp


#pragma once
#ifndef __index_buffer_hpp_
#define __index_buffer_hpp_

class IndexBuffer
{
public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void bind() const;
    inline unsigned int get_count() const { return m_count; }
private:
    unsigned int m_id;
    unsigned int m_count;
};

#endif  // __index_buffer_hpp_
