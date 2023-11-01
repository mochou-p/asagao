// asagao/includes/scene.hpp


#pragma once


#include <cstdio>
#include <vector>
#include <memory>


class Object
{
public:
    virtual inline void do_something() const noexcept = 0;
};

class GameObject : public Object
{
private:
    inline void do_something() const noexcept final { std::printf("hello GameObject\n"); }
};

class TileMap : public Object
{
private:
    inline void do_something() const noexcept final { std::printf("hello TileMap\n");    }
};


class Scene
{
public:
    Scene();
    ~Scene();

    inline auto new_object(std::unique_ptr<Object>&& object) { m_objects.push_back(std::move(object)); }

    void do_something_with_objects() const noexcept;

private:
    std::vector<std::unique_ptr<Object>> m_objects;
};
