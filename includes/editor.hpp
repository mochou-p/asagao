// asagao/includes/editor.hpp


#pragma once


#include "scene.hpp"

#include "imgui.h"

#include <memory>


typedef int ImGuiWindowFlags;

class       Window;


enum class EditorView
{
    Home,
    Scene
};


class Editor
{
public:
    Editor(Window& window, std::unique_ptr<Scene>& scene);
    ~Editor();

    void render() noexcept;

private:
    void home  ()       noexcept;
    void scene () const noexcept;

    inline void next_window_dimensions(const ImVec4& vector) const noexcept;

    const ImGuiWindowFlags m_ui_window_flags;

    ImVec2     m_window_size;
    EditorView m_current_view;

    Window&                 r_window;
    std::unique_ptr<Scene>& r_scene;
};
