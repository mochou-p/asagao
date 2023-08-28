// asagao/includes/shader.hpp


#pragma once
#ifndef __shader_hpp_
#define __shader_hpp_

#include <string>
#include <map>
#include "glm.hpp"

class Shader
{
public:
    Shader(const std::string& filepath);
    ~Shader();

    void use() const;
    void set_int(const std::string& name, int value);
    void set_mat4(const std::string& name, const glm::mat4& value);
private:
    int get_uniform_location(const std::string& name);

    unsigned int               m_id;
    std::map<std::string, int> m_uniform_location_cache;
};

#endif  // __shader_hpp_
