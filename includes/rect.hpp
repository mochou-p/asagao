// asagao/includes/rect.hpp


#pragma once
#ifndef __rect_hpp_
#define __rect_hpp_

#include <vector>
#include "glm.hpp"

class Rect
{
public:
    Rect(const float size, const glm::vec2& uv_fraction);
    ~Rect() {}

    inline const float* get_vertices() const
    { return m_vertices.data(); }

    inline size_t get_vertices_size() const
    { return sizeof(float) * m_vertices.size(); }

    inline const unsigned int* get_indices() const
    { return m_indices.data(); }

    inline unsigned int get_indices_count() const
    { return m_indices.size(); }

private:
    std::vector<float>        m_vertices;
    std::vector<unsigned int> m_indices;
};

#endif  // __rect_hpp_
