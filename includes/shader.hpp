// asagao/includes/shader.hpp


#pragma once
#ifndef __shader_hpp_
#define __shader_hpp_

#include "glad/glad.h"

class Shader
{
public:
    Shader(const std::string&);
    ~Shader();

    void use() { glUseProgram(m_id); }

    GLuint m_id;
};

#endif  // __shader_hpp_
