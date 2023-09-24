// asagao/includes/scene.hpp


#pragma once

#include <string>
#include <vector>
#include "game_object.hpp"

class Scene
{
public:
    Scene(const std::string& filepath);
    ~Scene() {}

    void save() const;

    std::vector<GameObject> objects;
    GameObject*             selected;
    std::string             name;
};
