// asagao/includes/scene.hpp


#pragma once

#include "game_object.hpp"

#include <string>
#include <vector>

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
