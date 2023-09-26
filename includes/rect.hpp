// asagao/includes/rect.hpp


#pragma once

#include "types.hpp"

#include <vector>

// 2 triangles
#define INDEX_COUNT 6
// 4 * (position(x, y), texcoord(u, v))
#define VERTEX_COUNT 16

class Rect
{
public:
    Rect(const f32 size, const v2& uv_fraction);

    inline const f32* get_vertices() const
    { return m_vertices; }

    inline u64 get_vertices_size() const
    { return VERTEX_COUNT * sizeof(f32); }

    inline const u32* get_indices() const
    { return m_indices; }

    inline u32 get_indices_count() const
    { return INDEX_COUNT; }

private:
    f32 m_vertices[VERTEX_COUNT];
    u32 m_indices[INDEX_COUNT];
};
