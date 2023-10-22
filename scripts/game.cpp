// asagao/scripts/game.cpp


#include "stdafx.h"

#include "game.hpp"


// example game


static GameObject* player;


void
Game::start() const
{
    player = &(Scene::find("Player"));
}

void
Game::update() const
{
    static const float speed = 1.5f;

    static v2 delta;
    delta = {0, 0};

    if (Input::is_down(Key::W)) delta.y += speed;
    if (Input::is_down(Key::A)) delta.x -= speed;
    if (Input::is_down(Key::S)) delta.y -= speed;
    if (Input::is_down(Key::D)) delta.x += speed;

    player->move(delta);
}
