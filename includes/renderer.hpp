// asagao/includes/renderer.hpp


#pragma once
#ifndef __renderer_hpp_
#define __renderer_hpp_

#include "vertex_array.hpp"
#include "index_buffer.hpp"
#include "shader.hpp"

class Renderer
{
public:
    Renderer() {}

    static void init();

    void clear() const;
    void draw(const VertexArray& va, const IndexBuffer& ib,
        const Shader& shader) const;

    static inline float zoom = 1.0f;
private:
    unsigned int m_id;
};

#endif  // __renderer_hpp_
