// asagao/source/program.cpp


#include <iostream>
#include "program.hpp"

#define OPENGL_ERROR_LEN 512

Program::Program(const std::list<GLuint>& t_shaders)
{
    m_id = glCreateProgram();

    for (const GLuint& shader : t_shaders)
        glAttachShader(m_id, shader);

    glLinkProgram(m_id);

    GLint success;
    char  error[OPENGL_ERROR_LEN];
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(m_id, OPENGL_ERROR_LEN, nullptr, error);
        std::cerr << "glLinkProgram failed" << std::endl << error
            << std::endl;
        exit(EXIT_FAILURE);
    }

    for (const GLuint& shader : t_shaders)
        glDeleteShader(shader);
}

Program::~Program()
{
    glDeleteProgram(m_id);
}
