// asagao/source/editor.cpp


#include "editor.hpp"

#include "window.hpp"

#include <cstdio>

#include "imgui.h"


Editor::Editor
(Window& window)
: m_ui_window_flags(ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)
,    m_current_view(EditorView::Home)
,          r_window(window)
{
    std::printf("Editor\n");
}

Editor::~Editor()
{
    std::printf("~Editor\n");
}


void
Editor::render() noexcept
{
    switch (m_current_view)
    {
        // c++20: using enum
    case EditorView::Home:   home(); break;
    case EditorView::Scene: scene(); break;

    default:
        std::printf("unknown EditorView (%d)\n", m_current_view);
        m_current_view = EditorView::Home;
        break;
    }
}

void
Editor::home() noexcept
{
    static const auto window_flags = m_ui_window_flags | ImGuiWindowFlags_NoTitleBar;

    static const auto window_pos = ImVec2(0.0f, 0.0f);
    ImGui::SetNextWindowPos(window_pos);

    const auto window_size = ImVec2(r_window.get_width(), r_window.get_height());
    ImGui::SetNextWindowSize(window_size);


    ImGui::Begin("## Home", nullptr, window_flags);
        static const auto button_size = ImVec2(120.0f, 30.0f);

        ImGui::SetCursorPosX((window_size.x - button_size.x) * 0.5f);
        ImGui::SetCursorPosY((window_size.y - button_size.y) * 0.5f);

        if (ImGui::Button("New scene", button_size))
            m_current_view = EditorView::Scene;
    ImGui::End();
}

void
Editor::scene() const noexcept
{
    static const auto window_pos = ImVec2(0.0f, 0.0f);
    ImGui::SetNextWindowPos(window_pos);

    const auto window_size = ImVec2(r_window.get_width() * 0.2f, r_window.get_height());
    ImGui::SetNextWindowSize(window_size);


    ImGui::Begin("Objects", nullptr, m_ui_window_flags);
    ImGui::End();
}
