// asagao/includes/shader.hpp


#pragma once
#ifndef __shader_hpp_
#define __shader_hpp_

#include "glad/glad.h"

class Shader
{
public:
    Shader(const std::string&);
    ~Shader() { glDeleteProgram(m_id); }

    void use() { glUseProgram(m_id); }
    void set_int(const std::string& t_location, int t_val)
    { glUniform1i(glGetUniformLocation(m_id, t_location.c_str()), t_val); }
private:
    GLuint m_id;
};

#endif  // __shader_hpp_
