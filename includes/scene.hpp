// asagao/includes/scene.hpp


#pragma once
#ifndef __scene_hpp_
#define __scene_hpp_

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
    GameObject* selected;
private:
    std::string m_name;
};

#endif  // __scene_hpp_
