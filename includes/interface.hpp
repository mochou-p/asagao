// asagao/includes/interface.hpp


#pragma once


class Window;


class Interface
{
public:
    Interface(Window& window);
    ~Interface();

    void init()   const;

    void render() const noexcept;

private:
    Window& r_window;
};
