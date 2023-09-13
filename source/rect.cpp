// asagao/source/rect.cpp


#include "rect.hpp"

Rect::Rect(const float size, const glm::vec2& uv_fraction)
{
    const float half_of_rect = size * 0.5f;

    m_vertices.emplace_back(-half_of_rect);  // x
    m_vertices.emplace_back(-half_of_rect);  // y
    m_vertices.emplace_back(0.0f);           // u
    m_vertices.emplace_back(0.0f);           // v

    m_vertices.emplace_back( half_of_rect);
    m_vertices.emplace_back(-half_of_rect);
    m_vertices.emplace_back(uv_fraction.x);
    m_vertices.emplace_back(0.0f);

    m_vertices.emplace_back( half_of_rect);
    m_vertices.emplace_back(half_of_rect);
    m_vertices.emplace_back(uv_fraction.x);
    m_vertices.emplace_back(uv_fraction.y);

    m_vertices.emplace_back(-half_of_rect);
    m_vertices.emplace_back(half_of_rect);
    m_vertices.emplace_back(0.0f);
    m_vertices.emplace_back(uv_fraction.y);

    m_vertices.shrink_to_fit();

    m_indices.emplace_back(0);  //   2
    m_indices.emplace_back(1);  //  /|
    m_indices.emplace_back(2);  // 0-1

    m_indices.emplace_back(2);  // 3-2
    m_indices.emplace_back(3);  // |/
    m_indices.emplace_back(0);  // 0

    m_indices.shrink_to_fit();
};
