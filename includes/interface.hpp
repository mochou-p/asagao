// asagao/includes/interface.hpp


#pragma once


class Window;
class Editor;


class Interface
{
public:
    Interface(Window& window, Editor& editor);
    ~Interface();

    void init()   const;

    void render() const noexcept;

private:
    Window& r_window;
    Editor& r_editor;
};
