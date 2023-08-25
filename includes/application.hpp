// asagao/includes/application.hpp


#pragma once
#ifndef __application_hpp_
#define __application_hpp_

#include <vector>

class Application
{
public:
    Application() {};

    void run() const;

    static inline std::vector<const char*> objects;
};

#endif  // __application_hpp_
