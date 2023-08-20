// asagao/includes/app.hpp


#pragma once
#ifndef __app_hpp_
#define __app_hpp_

#include <memory>
#include "window.hpp"
#include "gui.hpp"

class App
{
public:
    App(const std::string&, int, int);
    ~App() {}

    void run();
private:
    std::unique_ptr<Window> m_win;
    std::unique_ptr<Gui>    m_gui;
};

#endif  // __app_hpp_
