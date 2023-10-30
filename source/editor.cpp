// asagao/source/editor.cpp


#include "editor.hpp"

#include "window.hpp"

#include <cstdio>


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
    m_window_size = {r_window.get_width() * 1.0f, r_window.get_height() * 1.0f};

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

    ImGui::SetNextWindowPos  ({m_window_size.x * Interface::HomeX,     m_window_size.y * Interface::HomeY     });
    ImGui::SetNextWindowSize ({m_window_size.x * Interface::HomeWidth, m_window_size.y * Interface::HomeHeight});


    ImGui::Begin("## Home", nullptr, window_flags);
        const auto region = ImGui::GetContentRegionAvail();

        static const auto button_size = ImVec2(120.0f, 30.0f);

        ImGui::SetCursorPosX((region.x - button_size.x) * 0.5f);
        ImGui::SetCursorPosY((region.y - button_size.y) * 0.5f);

        if (ImGui::Button("New scene", button_size))
            m_current_view = EditorView::Scene;
    ImGui::End();
}

void
Editor::scene() const noexcept
{
    ImGui::SetNextWindowPos  ({m_window_size.x * Interface::ObjectsX,     m_window_size.y * Interface::ObjectsY     });
    ImGui::SetNextWindowSize ({m_window_size.x * Interface::ObjectsWidth, m_window_size.y * Interface::ObjectsHeight});


    ImGui::Begin("Objects", nullptr, m_ui_window_flags);
    ImGui::End();
}
