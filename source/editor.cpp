// asagao/source/editor.cpp


#include "editor.hpp"

#include "window.hpp"

#include <cstdio>

#include "imgui.h"


Editor::Editor
(Window& window)
: m_ui_window_flags(ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove)
, r_window(window)
{
    std::printf("Editor\n");
}

Editor::~Editor()
{
    std::printf("~Editor\n");
}

void
Editor::render() const noexcept
{
    static const auto window_pos = ImVec2(0.0f, 0.0f);
    ImGui::SetNextWindowPos(window_pos);

    const auto window_size = ImVec2(r_window.get_width(), r_window.get_height());
    ImGui::SetNextWindowSize(window_size);

    ImGui::Begin("## Starting screen", nullptr, m_ui_window_flags);
        static ImVec2 region;
        region = ImGui::GetContentRegionAvail();

        static const auto button_size = ImVec2(120.0f, 30.0f);

        ImGui::SetCursorPosX((region.x - button_size.x) * 0.5f);
        ImGui::SetCursorPosY((region.y - button_size.y) * 0.5f);

        ImGui::Button("New scene", button_size);
    ImGui::End();
}
