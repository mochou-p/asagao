// asagao/includes/objects.hpp


#pragma once
#ifndef __objects_hpp_
#define __objects_hpp_

#include <vector>
#include "glad/glad.h"

struct VAP
{
    GLint     size;
    GLsizei   stride;
    size_t    pointer;
    GLenum    type;
    GLboolean normalized;

    VAP(GLint     size,
        GLsizei   stride,
        size_t    pointer,
        GLenum    type       = GL_FLOAT,
        GLboolean normalized = GL_FALSE)
    :       size{size}
    ,     stride{stride}
    ,    pointer{pointer}
    ,       type{type}
    , normalized{normalized}
    {}
};

class BO
{
public:
    BO(const void* data, GLsizeiptr size, GLenum target);
    ~BO() { glDeleteBuffers(1, &m_id); }
private:
    GLuint m_id;
};

class VAO
{
public:
    VAO(const std::vector<VAP>& attribs);
    ~VAO() { glDeleteVertexArrays(1, &m_id); }

    void enable();
private:
    GLuint           m_id;
    std::vector<VAP> m_attribs;
};

#endif  // __objects_hpp_
