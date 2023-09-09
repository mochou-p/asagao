// asagao/includes/image.hpp


#pragma once
#ifndef __image_hpp_
#define __image_hpp_

#include <string>

class Image
{
public:
    Image(const std::string& filepath, bool flip_y = true);
    ~Image();

    inline int            get_width()  const { return m_width;  }
    inline int            get_height() const { return m_height; }
    inline unsigned char* get_data()   const { return m_data;   }
private:
    int            m_width;
    int            m_height;
    unsigned char* m_data;
};

#endif  // __image_hpp_
