// asagao/source/texture.cpp


#include <cstring>
#include "texture.hpp"
#include "log.hpp"
#include "glad/glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define TEXTURE_PATH "resources/"
#define DEFAULT_TEXTURE "texture/default.png"

Texture::Texture(const std::string& filepath)
{
    if (count >= 32)
        LOG_FATAL("maximum number of textures exceeded (32)");

    stbi_set_flip_vertically_on_load(true);

    int width, height, channels;
    stbi_uc* data;
    
    data = stbi_load((TEXTURE_PATH + filepath).c_str(), &width,
        &height, &channels, 4);

    if (!data)
    {
        if (filepath != DEFAULT_TEXTURE)
        {
            LOG_WARN("cannot find " + filepath);

            *this = Texture(DEFAULT_TEXTURE);
            return;
        }

        LOG_WARN("cannot find the fallback texture");

        width  = 2;
        height = 2;

        unsigned int texel_count = width * height;
        unsigned int array_count = 4 * texel_count;

        unsigned char texels[array_count] =
        {
            255,   0, 255, 255,       0,   0,   0, 255,
              0,   0,   0, 255,     255,   0, 255, 255
        };

        unsigned long long size = array_count * sizeof(unsigned char);

        data = (unsigned char*) malloc(size);
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

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
        GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_id);
}
