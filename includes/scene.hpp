// asagao/includes/scene.hpp


#pragma once


#include "game_object.hpp"


class Scene
{
public:
    Scene();
    Scene(const str& filepath);

    void save() const;
    void unload();

    std::vector<GameObject> objects;
    GameObject*             selected;
    str                     name;
};
