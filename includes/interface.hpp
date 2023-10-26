// asagao/includes/interface.hpp


#pragma once


class Window;


class Interface
{
public:
    Interface(Window& window);
    ~Interface();

    Interface(const Interface&) = delete;

private:
    Window& r_window;
};
