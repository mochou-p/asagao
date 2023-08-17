// asagao/source/shader.cpp


#include <iostream>
#include "shader.hpp"

Shader::Shader(const char* t_code, int t_stage)
{
    m_id = glCreateShader(t_stage);
    glShaderSource(m_id, 1, &t_code, nullptr);
    glCompileShader(m_id);

    GLint success;
    char  error[512];
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(m_id, 512, NULL, error);
        std::cerr << "glCompileShader failed" << std::endl << error
            << std::endl;
        exit(EXIT_FAILURE);
    }
}
