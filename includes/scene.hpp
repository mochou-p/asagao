// asagao/includes/scene.hpp


#pragma once


#include "game_object.hpp"


class Scene
{
public:
    Scene(const str& filepath);

    void save() const;

    std::vector<GameObject> objects;
    GameObject*             selected;
    str                     name;
};
