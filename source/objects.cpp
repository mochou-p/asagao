// asagao/source/objects.cpp


#include <iostream>
#include "objects.hpp"

BO::BO(const void* t_data, GLsizeiptr t_size, GLenum t_target)
{
    glGenBuffers(1, &m_id);
    glBindBuffer(t_target, m_id);
    glBufferData(t_target, t_size, t_data, GL_STATIC_DRAW);
}

VAO::VAO(const std::vector<VAP>& t_attribs)
{
    glGenVertexArrays(1, &m_id);
    glBindVertexArray(m_id);

    std::copy(t_attribs.begin(), t_attribs.end(),
        std::back_inserter(m_attribs));
}

void VAO::enable()
{
    GLuint i = 0;
    for (const VAP& a : m_attribs)
    {
        glVertexAttribPointer(i, a.size, a.type, a.normalized,
            a.stride, (const void*) a.pointer);
        glEnableVertexAttribArray(i++);
    }
}
