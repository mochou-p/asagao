// asagao/source/shader.cpp


#include "shader.hpp"

#include <cstdio>


Shader::Shader
(const std::string& name)
{
    std::printf("Shader (%s.glsl)\n", name.c_str());
}

Shader::~Shader()
{
    std::printf("~Shader\n");
}
