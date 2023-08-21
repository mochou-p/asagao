// asagao/source/app.cpp


#include <iostream>
#include <cmath>
#include "app.hpp"
#include "shader.hpp"
#include "utils.hpp"

App::App(const std::string& t_name, int t_width, int t_height)
{
    m_win = std::make_unique<Window>(t_name, t_width, t_height);
    m_gui = std::make_unique<Gui>();
}

void App::run()
{
    Shader test_shader("test.glsl");
    test_shader.use();
    test_shader.set_vec4("u_color", {0.3f, 1.0f, 0.0f, 1.0f});

    ////////////////////////////////////////////////////////////////////////////

    const float vertices[]
    {
        -0.2f, -0.2f,
         0.2f, -0.2f,
         0.0f,  0.05f,

         0.0f, -0.05f,
        -0.2f,  0.2f,
         0.2f,  0.2f
    };

    GLuint indices[]
    {
        0, 1, 2,
        3, 4, 5
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

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    while (m_win->is_open())
    {
        m_win->events();
        m_win->clear();

        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);

        m_gui->draw();

        m_win->swap_buffers();
    }

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &ebo);
}
