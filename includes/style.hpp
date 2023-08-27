// asagao/includes/style.hpp


#pragma once
#ifndef __style_hpp_
#define __style_hpp_

#include "glm.hpp"

struct layout
{
    glm::vec2 pos;
    glm::vec2 size;
};

class Layout
{
public:
    // these are fractions of the window's size
    static inline const layout objects    {{0.00f, 0.0f}, {0.20f, 1.0f}};
    static inline const layout scene      {{0.20f, 0.0f}, {0.60f, 1.0f}};
    static inline const layout components {{0.80f, 0.0f}, {0.20f, 1.0f}};
};

#endif  // __style_hpp_
