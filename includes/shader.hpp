// asagao/includes/shader.hpp


#pragma once

#include "glad/glad.h"

class Shader
{
public:
    Shader(const char*, int);
    ~Shader() {};

    GLuint m_id;
};
