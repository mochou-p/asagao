// asagao/includes/gui.hpp


#pragma once

#include "glfw3.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class Gui
{
public:
    Gui(GLFWwindow*);
    ~Gui();

    void draw();
private:
    ImVec2 get_window_size();
    void hierarchy();
    void scene();
    void inspector();
    void update_widgets();

    GLFWwindow* m_context;
};
