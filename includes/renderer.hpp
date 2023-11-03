// asagao/includes/renderer.hpp


#pragma once


#include "shader.hpp"

#include "glad/glad.h"
#include "glfw3.h"


struct Vector3
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};


class Renderer
{
public:
    Renderer();
    ~Renderer();

    void init() const;

    inline auto clear  ()                     const noexcept -> void { glClear(GL_COLOR_BUFFER_BIT);                  }
    inline auto set_bg (const Vector3& color) const noexcept -> void { glClearColor(color.x, color.y, color.z, 1.0f); }

private:
    Shader m_shader;
};
