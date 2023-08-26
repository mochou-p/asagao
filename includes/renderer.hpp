// asagao/includes/renderer.hpp


#pragma once
#ifndef __renderer_hpp_
#define __renderer_hpp_

#include "glad/glad.h"
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

    static inline float zoom = 0.01f;
    static inline bool  was_resized;
private:
    GLuint m_id;
};

#endif  // __renderer_hpp_
