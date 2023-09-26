// asagao/source/shader.cpp


#include "stdafx.h"

#include "shader.hpp"
#include "log.hpp"

#define SHADER_PATH "resources/shaders/"
#define SHADER_STAGE_TAG_START "#stage "
#define SHADER_STAGE_TAG_END "#endstage"

static u32
create_shader
(const str& code, u32 stage)
{
    u32 id = glCreateShader(stage);
    c_cstr code_cstr = code.c_str();

    glShaderSource(id, 1, &code_cstr, nullptr);
    glCompileShader(id);

    return id;
}

struct stage
{
    str tag;
    u32 type;
};

static void
parse_shader
(const str& filepath, u32 shader)
{
    static const std::vector<stage> stages
    {
        {"vertex",   GL_VERTEX_SHADER  },
        {"fragment", GL_FRAGMENT_SHADER}
    };

    std::ifstream ifs(SHADER_PATH + filepath);
    str code, line;

    while (std::getline(ifs, line))
    {
        if (line.find(SHADER_STAGE_TAG_START) == str::npos)
            continue;

        for (const stage& stage : stages)
        {
            if (line.find(stage.tag) == str::npos)
                continue;

            while (std::getline(ifs, line))
            {
                if (line.find(SHADER_STAGE_TAG_END) != str::npos)
                    break;

                code += line + "\n";
            }

            u32 shader_stage = create_shader(code, stage.type);
            glAttachShader(shader, shader_stage);
            glDeleteShader(shader_stage);

            code.clear();
            break;
        }
    }
}

Shader::Shader
(const str& filepath)
{
    m_id = glCreateProgram();
    parse_shader(filepath, m_id);
    glLinkProgram(m_id);
}

Shader::~Shader()
{
    glDeleteProgram(m_id);
}

void
Shader::use() const
{
    glUseProgram(m_id);
}

i32
Shader::get_uniform_location
(const str& name)
{
    if (m_uniform_location_cache.find(name) != m_uniform_location_cache.end())
        return m_uniform_location_cache[name];

    i32 location = glGetUniformLocation(m_id, name.c_str());

    if (location == -1)
    {
        LOG_WARN("cannot find a uniform location '" + name + "'");
        return -1;
    }

    m_uniform_location_cache[name] = location;
    return location;    
}

void
Shader::set_int
(const str& name, i32 value)
{
    glUniform1i(get_uniform_location(name), value);
}

void
Shader::set_mat4
(const str& name, const m4& value)
{
    glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, &value[0][0]);
}

void
Shader::set_vec2
(const str& name, const v2& value)
{
    glUniform2f(get_uniform_location(name), value.x, value.y);
}
