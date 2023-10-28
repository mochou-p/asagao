// asagao/includes/editor.hpp


#pragma once


typedef int ImGuiWindowFlags;


class Window;


class Editor
{
public:
    Editor(Window& window);
    ~Editor();

    void render() const noexcept;

private:
    const ImGuiWindowFlags m_ui_window_flags;

    Window& r_window;
};
