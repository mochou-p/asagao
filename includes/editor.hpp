// asagao/includes/editor.hpp


#pragma once


typedef int ImGuiWindowFlags;


class Window;


enum class EditorView
{
    Home,
    Scene
};


class Editor
{
public:
    Editor(Window& window);
    ~Editor();

    void render ()       noexcept;

private:
    void home   ()       noexcept;
    void scene  () const noexcept;

    const ImGuiWindowFlags m_ui_window_flags;

    EditorView m_current_view;

    Window& r_window;
};
