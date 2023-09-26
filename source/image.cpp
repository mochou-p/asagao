// asagao/source/image.cpp


#include "image.hpp"
#include "log.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Image::Image
(const str& filepath, bool flip_y)
{
    stbi_set_flip_vertically_on_load(flip_y);

    m_data = stbi_load(filepath.c_str(), &m_width, &m_height, nullptr, 4);

    if (!m_data)
        LOG_ERROR("failed to load " + filepath);
}

Image::~Image()
{
    stbi_image_free(m_data);
}
