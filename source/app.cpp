// asagao/source/app.cpp


#include <iostream>
#include <cmath>
#include "app.hpp"
#include "shader.hpp"
#include "program.hpp"

App::App(const char* t_name, int t_width, int t_height)
{
    m_win = std::make_unique<Window>(t_name, t_width, t_height);
    m_gui = std::make_unique<Gui>();
}

void App::run()
{
    Program program
    ({
        Shader("test.vert", GL_VERTEX_SHADER).m_id,
        Shader("test.frag", GL_FRAGMENT_SHADER).m_id
    });

    ////////////////////////////////////////////////////////////////////////////

    const float vertices[]
    {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
         0.5f,  0.5f, 0.0f
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
        program.use();
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        m_gui->draw();
        m_win->swap_buffers();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}
