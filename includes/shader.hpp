// asagao/includes/shader.hpp


#pragma once
#ifndef __shader_hpp_
#define __shader_hpp_

#include "glad/glad.h"
#include "utils.hpp"

class Shader
{
public:
    Shader(const std::string&);
    ~Shader();

    void use() { glUseProgram(m_id); }
    void set_vec4(const std::string& t_location, const vec4& t_val)
    { glUniform4f(glGetUniformLocation(m_id, t_location.c_str()), t_val.x,
        t_val.y, t_val.z, t_val.w); }

    GLuint m_id;
};

#endif  // __shader_hpp_
