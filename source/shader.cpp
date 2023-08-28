// asagao/source/shader.cpp


#include <vector>
#include <fstream>
#include <sstream>
#include "shader.hpp"
#include "utils.hpp"
#include "glad/glad.h"

#define SHADER_PATH "resources/shaders/"
#define SHADER_STAGE_TAG_START "#stage "
#define SHADER_STAGE_TAG_END "#endstage"

static unsigned int
create_shader
(
 const std::string& code,
       int          stage
)
{
    unsigned int id = glCreateShader(stage);
    const char* code_cstr = code.c_str();

    glShaderSource(id, 1, &code_cstr, nullptr);
    glCompileShader(id);

    opengl_check_error(id, GL_COMPILE_STATUS, "glCompileShader",
        &glGetShaderiv, &glGetShaderInfoLog);

    return id;
}

struct stage
{
    std::string tag;
    int         type;
};

static void
parse_shader
(
 const std::string& filepath,
       unsigned int shader
)
{
    static const std::vector<stage> stages
    {
        {"vertex",   GL_VERTEX_SHADER  },
        {"fragment", GL_FRAGMENT_SHADER}
    };

    std::ifstream ifs(SHADER_PATH + filepath);
    std::string   code, line;

    while (std::getline(ifs, line))
    {
        if (line.find(SHADER_STAGE_TAG_START) == std::string::npos)
            continue;

        for (const stage& s : stages)
        {
            if (line.find(s.tag) == std::string::npos)
                continue;

            while (std::getline(ifs, line))
            {
                if (line.find(SHADER_STAGE_TAG_END) != std::string::npos)
                    break;

                code += line + "\n";
            }

            unsigned int shader_stage = create_shader(code, s.type);
            glAttachShader(shader, shader_stage);
            glDeleteShader(shader_stage);

            code.clear();
            break;
        }
    }
}

Shader::Shader(const std::string& filepath)
{
    m_id = glCreateProgram();
    parse_shader(filepath, m_id);
    glLinkProgram(m_id);

    opengl_check_error(m_id, GL_LINK_STATUS, "glLinkProgram", &glGetProgramiv,
        &glGetProgramInfoLog);
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

int
Shader::get_uniform_location(const std::string& name)
{
    if (m_uniform_location_cache.find(name) != m_uniform_location_cache.end())
        return m_uniform_location_cache[name];

    int location = glGetUniformLocation(m_id, name.c_str());

    if (location == -1) quit("cannot find uniform location " + name);

    m_uniform_location_cache[name] = location;
    return location;    
}

void
Shader::set_int
(
 const std::string& name,
       int          value
)
{
    glUniform1i(get_uniform_location(name), value);
}

void
Shader::set_mat4
(
 const std::string& name,
 const glm::mat4&   value
)
{
    glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, &value[0][0]);
}
