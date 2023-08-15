// asagao/source/gui.cpp


#include <iostream>

#include "gui.hpp"

using namespace ImGui;

Gui::Gui(GLFWwindow* t_window_handle)
{
    IMGUI_CHECKVERSION();
    CreateContext();
    StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(t_window_handle, true);
    ImGui_ImplOpenGL3_Init();

    m_context = t_window_handle;
    
    std::cout << "ImGui\t" << IMGUI_VERSION << std::endl;
}

Gui::~Gui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    DestroyContext();
}

void new_frame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    NewFrame();
}

ImVec2 Gui::get_window_size()
{
    int width, height;
    glfwGetFramebufferSize(m_context, &width, &height);

    return {(float) width, (float) height};
}

void Gui::hierarchy()
{
    static const char             title[]     = "Hierarchy";
    static const ImGuiWindowFlags flags       = ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;
    static const ImVec2           window_size = get_window_size();
    static const ImVec2           size        = {window_size.x * 0.2f,
        window_size.y};
    static const ImVec2           pos         = {0.0f, 0.0f};

    SetNextWindowSize(size);
    SetNextWindowPos(pos);
    Begin(title, nullptr, flags);
    End();
}

void Gui::scene()
{
    static const char             title[]     = "Scene";
    static const ImGuiWindowFlags flags       = ImGuiWindowFlags_NoCollapse
        | ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoBackground;
    static const ImVec2           window_size = get_window_size();
    static const ImVec2           size        = {window_size.x * 0.6f,
        window_size.y};
    static const ImVec2           pos         = {window_size.x * 0.2f, 0.0f};

    SetNextWindowSize(size);
    SetNextWindowPos(pos);
    Begin(title, nullptr, flags);
    End();
}

void Gui::inspector()
{
    static const char             title[]     = "Inspector";
    static const ImGuiWindowFlags flags       = ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;
    static const ImVec2           window_size = get_window_size();
    static const ImVec2           size = {window_size.x * 0.2f,
        window_size.y};
    static const ImVec2           pos  = {window_size.x - size.x, 0.0f};

    SetNextWindowSize(size);
    SetNextWindowPos(pos);
    Begin(title, nullptr, flags);
    End();
}

void Gui::update_widgets()
{
    hierarchy();
    scene();
    inspector();
}

void render_gui()
{
    Render();
    ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());
}

void Gui::draw()
{
    new_frame();
    update_widgets();
    render_gui();
}
