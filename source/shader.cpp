// asagao/source/shader.cpp


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "shader.hpp"

#define OPENGL_ERROR_LEN 512
#define SHADER_DIR "resources/shaders/"

static std::string read_file(const std::string& t_filepath)
{
    std::stringstream ss;
    ss << std::ifstream(SHADER_DIR + t_filepath).rdbuf();

    return ss.str();
}

Shader::Shader(const std::string& t_filepath, int t_stage)
{
    m_id = glCreateShader(t_stage);

    std::string code      = read_file(t_filepath);
    const char* code_cstr = code.c_str();

    glShaderSource(m_id, 1, &code_cstr, nullptr);
    glCompileShader(m_id);

    GLint success;
    char  error[OPENGL_ERROR_LEN];
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(m_id, OPENGL_ERROR_LEN, NULL, error);
        std::cerr << "glCompileShader failed" << std::endl << error
            << std::endl;
        exit(EXIT_FAILURE);
    }
}
