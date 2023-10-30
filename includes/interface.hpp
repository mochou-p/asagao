// asagao/includes/interface.hpp


#pragma once


class Window;
class Editor;


class Interface
{
public:
    static constexpr auto    HomeX      = 0.3f;
    static constexpr auto    HomeY      = 0.4f;
    static constexpr auto    HomeWidth  = 0.4f;
    static constexpr auto    HomeHeight = 0.2f;

    static constexpr auto ObjectsX      = 0.0f;
    static constexpr auto ObjectsY      = 0.0f;
    static constexpr auto ObjectsWidth  = 0.2f;
    static constexpr auto ObjectsHeight = 1.0f;

public:
    Interface(Window& window, Editor& editor);
    ~Interface();

    void init()   const;

    void render() const noexcept;

private:
    Window& r_window;
    Editor& r_editor;
};
