// asagao/includes/shader.hpp


#pragma once
#ifndef __shader_hpp_
#define __shader_hpp_

#include <string>
#include "glad/glad.h"

class Shader
{
public:
    Shader(const std::string& filepath);
    ~Shader() { glDeleteProgram(m_id); }

    void use() { glUseProgram(m_id); }
    void set_int(const std::string& location, int val)
    { glUniform1i(glGetUniformLocation(m_id, location.c_str()), val); }
private:
    GLuint m_id;
};

#endif  // __shader_hpp_
