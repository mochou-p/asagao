// asagao/includes/app.hpp


#pragma once

#include "window.hpp"
#include "gui.hpp"

class App
{
public:
    App(const char*);
    ~App();

    void run();
private:
    Window* m_window;
    Gui*    m_interface;
};
