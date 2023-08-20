// asagao/includes/style.hpp


#pragma once
#ifndef __style_hpp_
#define __style_hpp_

#include "imgui.h"

struct layout
{
    ImVec2 pos;
    ImVec2 size;

    layout(float x, float y, float w, float h)
    :  pos(x, y)
    , size(w, h)
    {}
};

class Layout
{
public:
    // these are fractions of the window's size
    static inline const layout hierarchy {0.00f, 0.0f, 0.15f, 1.0f};
    static inline const layout scene     {0.15f, 0.0f, 0.70f, 1.0f};
    static inline const layout inspector {0.85f, 0.0f, 0.15f, 1.0f};
private:
    Layout();
};

#endif  // __style_hpp_
