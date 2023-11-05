// asagao/source/editor.cpp


#include "editor.hpp"

#include "window.hpp"

#include <cstdio>


Editor::Editor
(Window& window, std::unique_ptr<Scene>& scene)
: m_ui_window_flags(ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)
,    m_current_view(EditorView::Home)
,          r_window(window)
,           r_scene(scene)
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

    next_window_dimensions(Interface::Home);

    ImGui::Begin("## Home", nullptr, window_flags);
        static const auto text_width = ImGui::CalcTextSize("* Asagao").x;
        static const auto text_color = ImVec4_div_float({0.0f, 145.0f, 255.0f, 255.0f}, 255.0f);
        static const auto padding    = ImVec2(0.0f, 10.0f);

        const auto region_x = ImGui::GetContentRegionAvailWidth();

        ImGui::Dummy(padding);
        ImGui::SetCursorPosX((region_x - text_width) * 0.5f);
        ImGui::TextColored(text_color, "* Asagao");
        ImGui::Dummy(padding);
        ImGui::Separator();
        ImGui::Dummy(padding);

        static const auto button_size = ImVec2(100.0f, 30.0f);

        ImGui::SetCursorPosX((region_x - button_size.x) * 0.5f);

        if (ImGui::Button("New Game", button_size))
            m_current_view = EditorView::Scene;
    ImGui::End();
}

void
Editor::scene() const noexcept
{
    next_window_dimensions(Interface::Objects);

    ImGui::Begin("Objects", nullptr, m_ui_window_flags);
        for (const auto& obj : r_scene->m_objects)
            ImGui::Text(obj->get_name().c_str());
    ImGui::End();
}

void
Editor::next_window_dimensions
(const ImVec4& vector) const noexcept
{
    ImGui::SetNextWindowPos  (ImVec2_mul_ImVec2(m_window_size, {vector.x, vector.y}));
    ImGui::SetNextWindowSize (ImVec2_mul_ImVec2(m_window_size, {vector.z, vector.w}));
}
