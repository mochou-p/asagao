// asagao/source/shader.cpp


#include <iostream>
#include <fstream>
#include <sstream>
#include "shader.hpp"

std::string read_file(const char* t_filepath)
{
    std::ifstream ifs(std::string("resources/shaders/") + t_filepath);
    std::stringstream ss;
    ss << ifs.rdbuf();

    return ss.str();
}

Shader::Shader(const char* t_filepath, int t_stage)
{
    m_id = glCreateShader(t_stage);

    const char* code = read_file(t_filepath).c_str();

    glShaderSource(m_id, 1, &code, nullptr);
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
