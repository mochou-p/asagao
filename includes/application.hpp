// asagao/includes/application.hpp


#pragma once
#ifndef __application_hpp_
#define __application_hpp_

#include <vector>
#include "glm.hpp"

class Application
{
public:
    Application() {};

    void run() const;

    static inline std::vector<const char*> objects;

    static inline bool      view_changed = true;
    static inline glm::vec2 camera       = {0.0f, 0.0f};
    static inline glm::vec2 aspect;
};

#endif  // __application_hpp_
