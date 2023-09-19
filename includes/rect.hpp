// asagao/includes/rect.hpp


#pragma once
#ifndef __rect_hpp_
#define __rect_hpp_

#include <vector>
#include "glm.hpp"

// 2 triangles
#define INDEX_COUNT 6
// 4 * (position(x, y), texcoord(u, v))
#define VERTEX_COUNT 16

class Rect
{
public:
    Rect(const float size, const glm::vec2& uv_fraction);
    ~Rect() {}

    inline const float* get_vertices() const
    { return m_vertices; }

    inline size_t get_vertices_size() const
    { return VERTEX_COUNT * sizeof(float); }

    inline const unsigned int* get_indices() const
    { return m_indices; }

    inline unsigned int get_indices_count() const
    { return INDEX_COUNT; }

private:
    float        m_vertices[VERTEX_COUNT];
    unsigned int m_indices[INDEX_COUNT];
};

#endif  // __rect_hpp_
