// asagao/includes/game.hpp


#pragma once


#include "asagao.hpp"

#include "game_object.hpp"
#include "scene.hpp"


// later split these into scripting/

class Game
{
public:
    void start()  const;
    void update() const;

    bool running;
};

////////////////////////////////////

enum class Key
{
    W = GLFW_KEY_W,
    A = GLFW_KEY_A,
    S = GLFW_KEY_S,
    D = GLFW_KEY_D,

    F5 = GLFW_KEY_F5
};

class Input
{
public:
    static bool is_down(Key key) { return glfwGetKey(Asagao::Window.handle, static_cast<int>(key)); }
};
