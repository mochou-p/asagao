// asagao/includes/objects.hpp


#pragma once
#ifndef __objects_hpp_
#define __objects_hpp_

#include <vector>
#include "glad/glad.h"

struct VAP
{
    GLint       size;
    GLsizei     stride;
    size_t      pointer;
    GLenum      type;
    GLboolean   normalized;

    VAP(GLint t_size, GLsizei t_stride, size_t t_pointer,
        GLenum t_type = GL_FLOAT, GLboolean t_normalized = GL_FALSE)
    :       size(t_size)
    ,     stride(t_stride)
    ,    pointer(t_pointer)
    ,       type(t_type)
    , normalized(t_normalized)
    {}
};

class BO
{
public:
    BO(const void*, GLsizeiptr, GLenum);
    ~BO() { glDeleteBuffers(1, &m_id); }
private:
    GLuint m_id;
};

class VAO
{
public:
    VAO(const std::vector<VAP>&);
    ~VAO() { glDeleteVertexArrays(1, &m_id); }

    void enable();
private:
    GLuint m_id;
    std::vector<VAP> m_attribs;
};

#endif  // __objects_hpp_
