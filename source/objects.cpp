// asagao/source/objects.cpp


#include <algorithm>
#include "objects.hpp"

BO::BO(const void*      data,
             GLsizeiptr size,
             GLenum     target)
{
    glGenBuffers(1, &m_id);
    glBindBuffer(target, m_id);
    glBufferData(target, size, data, GL_STATIC_DRAW);
}

VAO::VAO(const std::vector<VAP>& attribs)
{
    glGenVertexArrays(1, &m_id);
    glBindVertexArray(m_id);

    std::copy(attribs.begin(), attribs.end(),
        std::back_inserter(m_attribs));
}

void
VAO::enable()
{
    GLuint i = 0;

    for (const VAP& a : m_attribs)
    {
        glVertexAttribPointer(i, a.size, a.type, a.normalized,
            a.stride, (const void*) a.pointer);
        glEnableVertexAttribArray(i++);
    }
}
