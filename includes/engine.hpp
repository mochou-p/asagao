// asagao/includes/engine.hpp


#pragma once


#include "window.hpp"
#include "editor.hpp"

#include <string>
// #include <memory>


class Engine
{
public:
    Engine(const std::string& window_title, const unsigned short window_width, const unsigned short window_height);
    ~Engine();

    Engine(const Engine&) = delete;

private:
    Window m_window;
    Editor m_editor;

    // std::unique_ptr<Scene> m_scene;
    // std::unique_ptr<Game>  m_game;
};
