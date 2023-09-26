// asagao/includes/image.hpp


#pragma once

class Image
{
public:
    Image(const str& filepath, bool flip_y = true);
    ~Image();

    inline i32 get_width()  const { return m_width;  }
    inline i32 get_height() const { return m_height; }
    inline u8* get_data()   const { return m_data;   }
private:
    i32 m_width;
    i32 m_height;
    u8* m_data;
};
