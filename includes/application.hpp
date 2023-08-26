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
    static inline glm::vec2                moving;
};

#endif  // __application_hpp_
