// asagao/includes/engine.hpp


#pragma once


#include "window.hpp"
#include "editor.hpp"

#include <string>


class Engine
{
public:
    Engine(const std::string& window_title, const unsigned short window_width, const unsigned short window_height);
    ~Engine();

    void start() const;

private:
    Window m_window;
    Editor m_editor;
};
