// asagao/includes/shader.hpp


#pragma once

#include "glad/glad.h"

class Shader
{
public:
    Shader(const std::string&, int);
    ~Shader() {}

    GLuint m_id;
};
