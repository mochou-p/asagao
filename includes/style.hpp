// asagao/includes/style.hpp


#pragma once


struct layout
{
    v2 pos;
    v2 size;
};


class Layout
{
public:
    // these are fractions of the window's size
    static inline const layout objects    {{0.00f, 0.0f}, {0.20f, 1.0f}};
    static inline const layout scene      {{0.20f, 0.0f}, {0.60f, 1.0f}};
    static inline const layout components {{0.80f, 0.0f}, {0.20f, 1.0f}};
};
