// asagao/includes/style.hpp


#pragma once


#define LAYOUT_POS(a) \
{a.pos.x * Window.size.x, a.pos.y * Window.size.y}

#define LAYOUT_SIZE(a) \
{a.size.x * Window.size.x, a.size.y * Window.size.y}


struct layout
{
    v2 pos;
    v2 size;
};


class Layout
{
public:
    // these are fractions of the window's size
    static inline const layout start      {{0.0f, 0.0f}, {1.0f, 1.0f}};
    static inline const layout objects    {{0.0f, 0.0f}, {0.2f, 0.6f}};
    static inline const layout assets     {{0.0f, 0.6f}, {0.2f, 0.4f}};
    static inline const layout scene      {{0.2f, 0.0f}, {0.6f, 1.0f}};
    static inline const layout components {{0.8f, 0.0f}, {0.2f, 1.0f}};
};
