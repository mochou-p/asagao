// asagao/includes/app.hpp


#pragma once

#include <memory>
#include "window.hpp"
#include "gui.hpp"

class App
{
public:
    App(const char*);
    ~App() {};

    void run();
private:
    std::unique_ptr<Window> m_win;
    std::unique_ptr<Gui>    m_gui;
};
