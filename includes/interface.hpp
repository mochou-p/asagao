// asagao/includes/interface.hpp


#pragma once


class Window;


class Interface
{
public:
    Interface(Window& window);
    ~Interface();

private:
    Window& r_window;
};
