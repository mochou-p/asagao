// asagao/includes/scene.hpp


#pragma once


#include <string>
#include <cstdio>
#include <vector>
#include <memory>


class Object
{
public:
    virtual inline std::string get_name() const noexcept = 0;

protected:
    Object(const std::string& name): m_name(name) {}

    std::string m_name;
};

class GameObject : public Object
{
public:
    GameObject(const std::string& name): Object(name) {}

private:
    inline std::string get_name() const noexcept final { return "[GameObject] " + m_name; }
};

class TileMap : public Object
{
public:
    TileMap(const std::string& name): Object(name) {}

private:
    inline std::string get_name() const noexcept final { return "[TileMap]    " + m_name; }
};


class Scene
{
public:
    Scene();
    ~Scene();

    inline auto new_object(std::unique_ptr<Object>&& object) -> void { m_objects.push_back(std::move(object)); }

//private:
    std::vector<std::unique_ptr<Object>> m_objects;
};
