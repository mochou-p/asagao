// asagao/includes/shader.hpp


#pragma once

#include "types.hpp"

#include <map>

class Shader
{
public:
    Shader(const str& filepath);
    ~Shader();

    void use() const;
    void set_int(const str& name, i32 value);
    void set_mat4(const str& name, const m4& value);
    void set_vec2(const str& name, const v2& value);
private:
    i32 get_uniform_location(const str& name);

    u32 m_id;
    std::map<str, i32> m_uniform_location_cache;
};
