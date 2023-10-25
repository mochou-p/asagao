// asagao/source/renderer.cpp


#include "renderer.hpp"

#include <cstdio>


#define DEFAULT_SHADER "tile"


Renderer::Renderer()
: m_shader(DEFAULT_SHADER)
{
    std::printf("Renderer\n");
}

Renderer::~Renderer()
{
    std::printf("~Renderer\n");
}
