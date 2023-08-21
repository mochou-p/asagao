// asagao/source/shader.cpp


#include <vector>
#include <fstream>
#include <sstream>
#include "shader.hpp"
#include "utils.hpp"

#define SHADER_PATH "resources/shaders/"
#define SHADER_STAGE_TAG_START "#stage "
#define SHADER_STAGE_TAG_END "#endstage"

static GLuint create_shader(const std::string& t_code, int t_stage)
{
    GLuint id = glCreateShader(t_stage);
    const char* code_cstr = t_code.c_str();

    glShaderSource(id, 1, &code_cstr, nullptr);
    glCompileShader(id);

    opengl_check_error(id, GL_COMPILE_STATUS, "glCompileShader", &glGetShaderiv,
        &glGetShaderInfoLog);

    return id;
}

struct stage
{
    std::string tag;
    GLint       type;

    stage(const std::string& t_tag, GLint t_type)
    :  tag(t_tag)
    , type(t_type)
    {}
};

static void parse_shader(const std::string& t_filepath, GLuint t_shader)
{
    static const std::vector<stage> stages
    {
        {"vertex",   GL_VERTEX_SHADER  },
        {"fragment", GL_FRAGMENT_SHADER}
    };

    std::ifstream ifs(SHADER_PATH + t_filepath);
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
            glAttachShader(t_shader, shader_stage);
            glDeleteShader(shader_stage);

            code.clear();
            break;
        }
    }
}

Shader::Shader(const std::string& t_filepath)
{
    m_id = glCreateProgram();
    parse_shader(t_filepath, m_id);
    glLinkProgram(m_id);

    opengl_check_error(m_id, GL_LINK_STATUS, "glLinkProgram", &glGetProgramiv,
        &glGetProgramInfoLog);
}
