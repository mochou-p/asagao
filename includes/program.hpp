// asagao/includes/program.hpp


#pragma once

#include <vector>
#include <list>
#include "glad/glad.h"

class Program
{
public:
    Program(const std::list<GLuint>&);
    ~Program();

    void use();

    GLuint m_id;
};
