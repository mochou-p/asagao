// asagao/source/scene.cpp


#include "scene.hpp"


Scene::Scene()
{
    std::printf("Scene\n");
}

Scene::~Scene()
{
    std::printf("~Scene\n");
}


void
Scene::do_something_with_objects() const noexcept
{
    for (const auto& object : m_objects)
        object->do_something();
}
