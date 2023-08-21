// asagao/source/app.cpp


#include <iostream>
#include <cmath>
#include "app.hpp"
#include "shader.hpp"
#include "utils.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

App::App(const std::string& t_name, int t_width, int t_height)
{
    m_win = std::make_unique<Window>(t_name, t_width, t_height);
    m_gui = std::make_unique<Gui>();
}

void App::run()
{
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    stbi_uc* tex_data = stbi_load("resources/textures/saber.png", &width,
        &height, &channels, 4);

    if (!tex_data) quit("stbi_load failed");

    GLuint tex;
    glGenTextures(1, &tex);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
        GL_UNSIGNED_BYTE, tex_data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(tex_data);

    ////////////////////////////////////////////////////////////////////////////

    Shader test_shader("test.glsl");
    test_shader.use();
    test_shader.set_int("u_texture", 0);

    ////////////////////////////////////////////////////////////////////////////

    const float vertices[]
    {
    //  position     | tex coords
    //  x      y     | u    v
       -0.2f, -0.2f,   0,   0,
        0.2f, -0.2f,   1,   0,
        0.2f,  0.2f,   1,   1,
       -0.2f,  0.2f,   0,   1
    };

    const GLuint indices[]
    {
        0, 1, 2,
        2, 3, 0
    };

    const GLsizei count = sizeof(indices) / sizeof(GLuint);

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

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
        (void*) (2 * sizeof(float)));
    glEnableVertexAttribArray(1);

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
    glDeleteTextures(1, &tex);
}
