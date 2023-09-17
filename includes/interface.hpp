// asagao/includes/interface.hpp


#pragma once
#ifndef __interface_hpp_
#define __interface_hpp_

#include <functional>

class Interface;

using ViewFunction = void (Interface::*)();

class Interface
{
public:
    Interface();
    ~Interface();

    void draw();
private:
    void startup_view();
    void scene_view();
    void details();

    unsigned char         m_current_view;
    std::function<void()> m_views[2];
};

#endif  // __interface_hpp_
