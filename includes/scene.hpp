// asagao/includes/scene.hpp


#pragma once
#ifndef __scene_hpp_
#define __scene_hpp_

#include <string>

class Scene
{
public:
    static void load(const std::string& name);
    static void save(const std::string& name);
};

#endif  // __scene_hpp_
