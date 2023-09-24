// asagao/includes/shader.hpp


#pragma once

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
    void set_vec2(const std::string& name, const glm::vec2& value);
private:
    int get_uniform_location(const std::string& name);

    unsigned int               m_id;
    std::map<std::string, int> m_uniform_location_cache;
};
