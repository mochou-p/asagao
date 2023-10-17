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
    static inline const layout objects    {{0.0f, 0.0f}, {0.2f, 0.5f}};
    static inline const layout assets     {{0.0f, 0.5f}, {0.2f, 0.5f}};
    static inline const layout scene      {{0.2f, 0.0f}, {0.6f, 1.0f}};
    static inline const layout components {{0.8f, 0.0f}, {0.2f, 1.0f}};
};
