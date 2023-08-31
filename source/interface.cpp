// asagao/source/interface.cpp


#include "interface.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "window.hpp"
#include "style.hpp"
#include "application.hpp"
#include "renderer.hpp"

using namespace ImGui;

static void
set_theme()
{
    ImGuiStyle& style = GetStyle();
    style.WindowBorderSize = 0.0f;

    ImVec4* colors = style.Colors;
    colors[ImGuiCol_TitleBg]          = {0.3f, 0.3f, 0.3f, 1.0f};
    colors[ImGuiCol_TitleBgActive]    = {0.3f, 0.3f, 0.3f, 1.0f};
    colors[ImGuiCol_WindowBg]         = {0.2f, 0.2f, 0.2f, 1.0f};

    colors[ImGuiCol_FrameBg]          = {0.3f, 0.3f, 0.3f, 1.0f};
    colors[ImGuiCol_FrameBgHovered]   = {0.4f, 0.4f, 0.4f, 1.0f};
    colors[ImGuiCol_FrameBgActive]    = {0.5f, 0.5f, 0.5f, 1.0f};

    colors[ImGuiCol_CheckMark]        = {1.0f, 1.0f, 1.0f, 1.0f};

    colors[ImGuiCol_Button]           = {0.3f, 0.3f, 0.3f, 1.0f};
    colors[ImGuiCol_ButtonHovered]    = {0.4f, 0.4f, 0.4f, 1.0f};
    colors[ImGuiCol_ButtonActive]     = {0.5f, 0.5f, 0.5f, 1.0f};

    colors[ImGuiCol_HeaderHovered]    = {0.4f, 0.4f, 0.4f, 1.0f};
    colors[ImGuiCol_HeaderActive]     = {0.5f, 0.5f, 0.5f, 1.0f};

    colors[ImGuiCol_Separator]        = {0.5f, 0.5f, 0.5f, 1.0f};
    colors[ImGuiCol_SeparatorHovered] = {0.5f, 0.5f, 0.5f, 1.0f};
    colors[ImGuiCol_SeparatorActive]  = {0.5f, 0.5f, 0.5f, 1.0f};

    colors[ImGuiCol_SliderGrab]       = {0.6f, 0.6f, 0.6f, 1.0f};
    colors[ImGuiCol_SliderGrabActive] = {0.8f, 0.8f, 0.8f, 1.0f};
}

Interface::Interface()
{
    IMGUI_CHECKVERSION();

    CreateContext();
    StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(Window::handle, true);
    ImGui_ImplOpenGL3_Init();

    GetIO().IniFilename = nullptr;
    set_theme();
}

Interface::~Interface()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    DestroyContext();
}

static void
new_frame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    NewFrame();
}

static void
objects()
{
    static const char*            title    = "Objects";
    static const ImGuiWindowFlags flags    = ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
    static const ImVec4           darkened = {1.0f, 1.0f, 1.0f, 0.4f};
    static const float            new_btn  = CalcTextSize("+ ").x;

    SetNextWindowPos
    ({
        Layout::objects.pos.x * Window::size.x,
        Layout::objects.pos.y * Window::size.y
    });
    SetNextWindowSize
    ({
        Layout::objects.size.x * Window::size.x,
        Layout::objects.size.y * Window::size.y
    });

    Begin(title, nullptr, flags);

    Text("Demo scene");
    SameLine(GetWindowContentRegionMax().x - new_btn);
    if (Button("+")) Application::new_object();

    Separator();

    for (GameObject& obj : Application::objects)
    {
        if (!obj.visible) PushStyleColor(ImGuiCol_Text, darkened);

        if (Selectable(obj.name.c_str()))
            Application::selected_obj = &obj;

        if (!obj.visible) PopStyleColor();
    }

    End();
}

static void
components()
{
    static const char*                title = "Components";
    static const ImGuiWindowFlags     flags = ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;

    SetNextWindowPos
    ({
        Layout::components.pos.x * Window::size.x,
        Layout::components.pos.y * Window::size.y
    });
    SetNextWindowSize
    ({
        Layout::components.size.x * Window::size.x,
        Layout::components.size.y * Window::size.y
    });

    Begin(title, nullptr, flags);

    if (!Application::selected_obj)
    {
        TextDisabled("Select an object");

        End();
        return;
    }

    Checkbox(Application::selected_obj->name.c_str(),
        &Application::selected_obj->visible);

    Separator();

    Text("Position");
    DragFloat("X", &Application::selected_obj->position.x, 1.0f,
        -100000.0f, 100000.0f);
    DragFloat("Y", &Application::selected_obj->position.y, 1.0f,
        -100000.0f, 100000.0f);
    DragFloat("Depth", &Application::selected_obj->depth, 0.2f,
        -1000.0f, 1000.0f);

    Separator();

    Separator();

    Text("Size");
    // space here since label == tag/id in imgui
    DragFloat("X ", &Application::selected_obj->scale.x, 0.01f,
        -500.0f, 500.0f);
    DragFloat("Y ", &Application::selected_obj->scale.y, 0.01f,
        -500.0f, 500.0f);

    Separator();

    Text("Rotation");
    SliderFloat("Degrees", &Application::selected_obj->rotation,
        0.0f, 360.0f);

    End();
}

static void
update_widgets()
{
    objects();
    components();
}

static void
render_draw_data()
{
    Render();
    ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());
}

void
Interface::draw() const
{
    new_frame();
    update_widgets();
    render_draw_data();
}
