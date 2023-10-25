// asagao/includes/renderer.hpp


#pragma once


#include "shader.hpp"


class Renderer
{
public:
    Renderer();
    ~Renderer();

private:
    Shader m_shader;
};
