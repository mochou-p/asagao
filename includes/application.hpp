// asagao/includes/application.hpp


#pragma once
#ifndef __application_hpp_
#define __application_hpp_

#include <string>
#include <vector>
#include <initializer_list>
#include <deque>
#include <memory>
#include "glm.hpp"
#include "texture.hpp"
#include "renderer.hpp"
#include "scene.hpp"
#include "camera.hpp"

class Application
{
public:
    void run();

    static inline bool view_changed = true;

    static inline glm::vec2 aspect;
    static inline Camera camera;

    static inline       float     animation_speed =   1.7f;
    static inline const float     rect_size       = 100.0f;
    static inline       glm::vec2 uv_frac;

    static inline std::unique_ptr<Scene> scene;
};

#endif  // __application_hpp_
