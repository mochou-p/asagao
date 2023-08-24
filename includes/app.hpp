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
    App(const std::string& name, int width, int height);
    ~App() {}

    void run();
private:
    std::unique_ptr<Window> m_window;
    std::unique_ptr<Gui>    m_interface;
};

#endif  // __app_hpp_
