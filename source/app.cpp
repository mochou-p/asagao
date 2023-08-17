// asagao/source/app.cpp


#include <iostream>
#include <cmath>
#include "app.hpp"

App::App(const char* t_name)
{
    m_win = std::make_unique<Window>(t_name);
    m_gui = std::make_unique<Gui>(m_win->m_handle);
}

void App::run()
{
    // for checks
    GLint success;
    char  error[512];

    // vertex shader
    const char* vert_shader_code =
        "#version 460 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
        "}\0";

    GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert_shader, 1, &vert_shader_code, nullptr);
    glCompileShader(vert_shader);

    glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vert_shader, 512, NULL, error);
        std::cerr << "glCompileShader(vert_shader) failed: " << error
            << std::endl;
    }

    // fragment shader
    const char* frag_shader_code =
        "#version 460 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(1.0f, 0.0f, 0.1f, 1.0f);\n"
        "}\0";

    GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_shader, 1, &frag_shader_code, nullptr);
    glCompileShader(frag_shader);

    glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(frag_shader, 512, nullptr, error);
        std::cerr << "glCompileShader(frag_shader) failed: " << error
            << std::endl;
    }

    // shader program
    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vert_shader);
    glAttachShader(shader_program, frag_shader);
    glLinkProgram(shader_program);

    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program, 512, nullptr, error);
        std::cerr << "glLinkProgram(shader_program) failed: " << error
            << std::endl;
    }

    // shader cleanup
    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);

    // triangle geometry
    const float verts[]
    {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f
    };

    GLsizei vert_count = sizeof(verts) / sizeof(float) / 3;

    // vertex array object
    GLuint vao;
    glGenVertexArrays(1, &vao);

    // vertex buffer object
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);  
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    // tell opengl how to understand the geometry in memory
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
        nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (m_win->is_open())
    {
        glUseProgram(shader_program);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, vert_count);

        m_gui->draw();
        m_win->swap_buffers();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shader_program);
}
