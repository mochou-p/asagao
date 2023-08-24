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
    ~Renderer() {}

    void clear() { glClear(GL_COLOR_BUFFER_BIT); }
    void draw(VertexArray& va, IndexBuffer& ib, Shader& shader);
private:
    GLuint m_id;
};

#endif  // __renderer_hpp_
