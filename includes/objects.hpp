// asagao/includes/objects.hpp


#pragma once
#ifndef __objects_hpp_
#define __objects_hpp_

#include <vector>
#include "glad/glad.h"
#include "utils.hpp"

struct VertexAttribute
{
    GLuint    count;
    GLenum    type;
    GLboolean normalized;

    static GLuint
    get_size_of_type(GLenum type)
    {
        switch (type)
        {
            case GL_FLOAT: return 4;
        }

        quit("unsupported VertexAttribute type");
        return 0;
    }
};

class VertexBufferLayout
{
public:
    VertexBufferLayout()
    : m_stride{0}
    {}

    void push(GLuint count, GLenum type);
    GLuint get_stride() { return m_stride; }
    const std::vector<VertexAttribute>& get_attributes()
    { return m_attributes; }
private:
    std::vector<VertexAttribute> m_attributes;
    GLuint m_stride;
};

class VertexBuffer
{
public:
    VertexBuffer(const void* data, GLsizeiptr size);
    ~VertexBuffer() { glDeleteBuffers(1, &m_id); }

    void bind() { glBindBuffer(GL_ARRAY_BUFFER, m_id); }
private:
    GLuint m_id;
};

class IndexBuffer
{
public:
    IndexBuffer(const GLuint* data, GLuint count);
    ~IndexBuffer() { glDeleteBuffers(1, &m_id); }

    void bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id); }
    GLuint get_count() { return m_count; }
private:
    GLuint m_id;
    GLuint m_count;
};

class VertexArray
{
public:
    VertexArray()  { glGenVertexArrays(1, &m_id); }
    ~VertexArray() { glDeleteVertexArrays(1, &m_id); }

    void bind() { glBindVertexArray(m_id); }
    void add_vertex_buffer(VertexBuffer& vb, VertexBufferLayout& layout);
private:
    GLuint m_id;
};

#endif  // __objects_hpp_
