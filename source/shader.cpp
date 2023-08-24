// asagao/source/shader.cpp


#include <vector>
#include <fstream>
#include <sstream>
#include "shader.hpp"
#include "utils.hpp"

#define SHADER_PATH "resources/shaders/"
#define SHADER_STAGE_TAG_START "#stage "
#define SHADER_STAGE_TAG_END "#endstage"

static GLuint
create_shader(const std::string& code,
                    int          stage)
{
    GLuint id = glCreateShader(stage);
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
    GLint       type;

    stage(const std::string& tag,
                GLint        type)
    :  tag{tag}
    , type{type}
    {}
};

static void
parse_shader(const std::string& filepath,
                   GLuint       shader)
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

            GLuint shader_stage = create_shader(code, s.type);
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
