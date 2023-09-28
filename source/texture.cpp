// asagao/source/texture.cpp


#include "stdafx.h"

#include "texture.hpp"
#include "log.hpp"
#include "image.hpp"


#define DEFAULT_TEXTURE "textures/default.png"


Texture::Texture
(const str& filepath, bool flip_y)
{
    if (count >= 32)
        LOG_FATAL("maximum number of textures exceeded (32)");
    
    Image image(filepath, flip_y);

    auto data   = image.get_data();
    auto width  = image.get_width();
    auto height = image.get_height();

    if (!data)
    {
        if (filepath != DEFAULT_TEXTURE)
        {
            LOG_WARN(IMAGE_PATH + ("cannot find " + filepath));

            *this = Texture(DEFAULT_TEXTURE);

            return;
        }

        LOG_WARN("cannot find the fallback texture");

        width  = 2;
        height = 2;

        u32 texel_count = width * height;
        u32 array_count = 4 * texel_count;

        u8 texels[array_count] =
        {
            255,   0, 255, 255,       0,   0,   0, 255,
              0,   0,   0, 255,     255,   0, 255, 255
        };

        u64 size = array_count * sizeof(u8);

        data = (u8*) malloc(size);
        std::memcpy(data, texels, size);
    }

    m_slot = count;
    m_size = {width, height};

    glGenTextures(1, &m_id);
    glActiveTexture(GL_TEXTURE0 + (count++));
    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_id);
}
