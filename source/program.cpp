// asagao/source/program.cpp


#include <iostream>
#include "program.hpp"

Program::Program(const std::list<GLuint>& t_shaders)
{
    m_id = glCreateProgram();

    for (const GLuint& shader : t_shaders)
        glAttachShader(m_id, shader);

    glLinkProgram(m_id);

    GLint success;
    char  error[512];
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_id, 512, nullptr, error);
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

void Program::use()
{
    glUseProgram(m_id);
}
