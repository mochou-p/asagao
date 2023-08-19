// asagao/includes/shader.hpp


#pragma once

#include "glad/glad.h"

class Shader
{
public:
    Shader(const std::string&);
    ~Shader();

    void use() { glUseProgram(m_id); }

    GLuint m_id;
};
