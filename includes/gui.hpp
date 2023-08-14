// asagao/includes/gui.hpp


#pragma once

#include "glfw3.h"

class Gui
{
public:
    Gui(GLFWwindow*);
    ~Gui();

    void draw();
};
