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

    void use() { glUseProgram(m_id); }

    GLuint m_id;
};
