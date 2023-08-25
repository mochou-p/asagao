// asagao/includes/shader.hpp


#pragma once
#ifndef __shader_hpp_
#define __shader_hpp_

#include <string>
#include "glad/glad.h"
#include "glm.hpp"

class Shader
{
public:
    Shader(const std::string& filepath);
    ~Shader();

    void use() const;
    void set_int(const std::string& location, int value) const;
    void set_mat4(const std::string& location, const glm::mat4& value) const;
private:
    GLuint m_id;
};

#endif  // __shader_hpp_
