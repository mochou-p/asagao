// asagao/source/rect.cpp


#include "rect.hpp"

Rect::Rect
(const f32 size, const v2& uv_fraction)
{
    const f32 half_of_rect = size * 0.5f;

    m_vertices[ 0] = -half_of_rect;  // x
    m_vertices[ 1] = -half_of_rect;  // y
    m_vertices[ 2] = 0.0f;           // u
    m_vertices[ 3] = 0.0f;           // v

    m_vertices[ 4] =  half_of_rect;
    m_vertices[ 5] = -half_of_rect;
    m_vertices[ 6] = uv_fraction.x;
    m_vertices[ 7] = 0.0f;

    m_vertices[ 8] =  half_of_rect;
    m_vertices[ 9] = half_of_rect;
    m_vertices[10] = uv_fraction.x;
    m_vertices[11] = uv_fraction.y;

    m_vertices[12] = -half_of_rect;
    m_vertices[13] = half_of_rect;
    m_vertices[14] = 0.0f;
    m_vertices[15] = uv_fraction.y;

    m_indices[0] = 0;  //   2
    m_indices[1] = 1;  //  /|
    m_indices[2] = 2;  // 0-1

    m_indices[3] = 2;  // 3-2
    m_indices[4] = 3;  // |/
    m_indices[5] = 0;  // 0
}
