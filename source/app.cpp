// asagao/source/app.cpp


#include <iostream>
#include <cmath>
#include "app.hpp"
#include "shader.hpp"

App::App(const char* t_name)
{
    m_win = std::make_unique<Window>(t_name);
    m_gui = std::make_unique<Gui>(m_win->m_handle);
}

void App::run()
{
    const char* vert_shader_code =
        "#version 460 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
        "}\0";

    const char* frag_shader_code =
        "#version 460 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(0.92f, 0.2f, 0.58f, 1.0f);\n"
        "}\0";

    Shader vert_shader(vert_shader_code, GL_VERTEX_SHADER);
    Shader frag_shader(frag_shader_code, GL_FRAGMENT_SHADER);

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vert_shader.m_id);
    glAttachShader(shader_program, frag_shader.m_id);
    glLinkProgram(shader_program);

    GLint success;
    char  error[512];
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program, 512, nullptr, error);
        std::cerr << "glLinkProgram(shader_program) failed: " << error
            << std::endl;
    }

    glDeleteShader(vert_shader.m_id);
    glDeleteShader(frag_shader.m_id);

    ////////////////////////////////////////////////////////////////////////////

    const float vertices[]
    {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f, 0.0f
    };

    GLuint indices[]
    {
        0, 1, 2,
        2, 3, 1
    };

    GLsizei count = sizeof(indices) / sizeof(GLuint);

    GLuint vbo, vao, ebo;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);  
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
        GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
        nullptr);
    glEnableVertexAttribArray(0);

    while (m_win->is_open())
    {
        glUseProgram(shader_program);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        m_gui->draw();
        m_win->swap_buffers();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shader_program);
}
