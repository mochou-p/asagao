// asagao/source/renderer.cpp


#include "renderer.hpp"

void
Renderer::draw(VertexArray& va,
               IndexBuffer& ib,
               Shader&      shader)
{
    shader.use();
    va.bind();
    ib.bind();

    glDrawElements(GL_TRIANGLES, ib.get_count(), GL_UNSIGNED_INT, nullptr);
}
