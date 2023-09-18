// asagao/includes/interface.hpp


#pragma once
#ifndef __interface_hpp_
#define __interface_hpp_

#include <functional>

#define STARTUP_VIEW 0
#define SCENE_VIEW 1
#define VIEW_COUNT 2

class Interface;

using ViewFunction = void (Interface::*)();

class Interface
{
public:
    Interface();
    ~Interface();

    static inline const unsigned char get_view() { return current_view; }

    void draw();
private:
    void startup_view();
    void scene_view();
    void details();

    static inline unsigned char current_view = 0;

    std::function<void()> m_views[VIEW_COUNT];
};

#endif  // __interface_hpp_
