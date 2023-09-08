// asagao/source/scene.cpp


#include <fstream>
#include <sstream>
#include "scene.hpp"
#include "application.hpp"

#define SCENE_PATH "resources/scenes"
#define SCENE_EXT ".asagao"
#define SCENE_VER "0.0.1"
#define SCENE_HEADER_TOP "### Asagao Scene File ###"
#define SCENE_HEADER_OBJ "--- Scene Objects -------"

// temp
// expecting that users did not "corrupt" the scene file
// or atleast kept the same format and logic as Scene::save
Scene::Scene(const std::string& name)
: selected{nullptr}
, m_name{name}
{
    std::ifstream file(SCENE_PATH + ("/" + name) + SCENE_EXT);

    if (!file.is_open())
    {
        LOG_ERROR("failed to open " + name);
        return;
    }

    std::string line, temp, num;

    while (std::getline(file, line))
    {
        if (line == SCENE_HEADER_OBJ)
        {
            std::getline(file, line);
            break;
        }
    }

    std::size_t help;
    float x, y;

    std::string obj_name;
    glm::vec3 obj_position(0.0f), obj_scale(1.0f);
    float obj_depth, obj_rotation;
    bool obj_visible;
    unsigned long long obj_sprite_count;
    std::vector<glm::vec2> obj_sprite_offsets;

    while (!file.eof())
    {
        GameObject obj;

        // name
        std::getline(file, line);
        obj_name = line.substr(line.find(" ") + 1);

        // position
        std::getline(file, line);
        temp = line.substr(line.find(" ") + 1);
        help = temp.find(",");
        obj_position.x  = std::stof(temp.substr(0, help));
        obj_position.y  = std::stof(temp.substr(help + 1));
        obj_position   *= Application::rect_size;

        // depth
        std::getline(file, line);
        obj_depth = std::stof(line.substr(line.find(" ") + 1));

        // scale
        std::getline(file, line);
        temp = line.substr(line.find(" ") + 1);
        help = temp.find(",");
        obj_scale.x = std::stof(temp.substr(0, help));
        obj_scale.y = std::stof(temp.substr(help + 1));

        // rotation
        std::getline(file, line);
        obj_rotation = std::stof(line.substr(line.find(" ") + 1));

        // visible
        std::getline(file, line);
        obj_visible = std::stoi(line.substr(line.find(" ") + 1));

        // sprite count
        std::getline(file, line);
        obj_sprite_count = std::stoull(line.substr(line.find(" ") + 1));

        // sprite offsets
        std::getline(file, line);
        std::istringstream iss(line.substr(line.find(" ") + 1));
        obj_sprite_offsets.clear();
        while (std::getline(iss, temp, ','))
        {
            x = std::stof(temp);
            std::getline(iss, temp, ',');
            y = std::stof(temp);

            obj_sprite_offsets.push_back
            (
                glm::vec2(x, y) * Application::uv_frac
            );
        }

        objects.emplace_back
        (
            obj_name,
            obj_position,
            obj_depth,
            obj_scale,
            obj_rotation,
            obj_visible,
            obj_sprite_count,
            obj_sprite_offsets
        );

        std::getline(file, line);
    }
}

void
Scene::save() const
{
    std::ofstream file(SCENE_PATH + ("/" + m_name) + SCENE_EXT);

    if (!file.is_open())
    {
        LOG_ERROR("failed to open " + m_name);
        return;
    }

    file << SCENE_HEADER_TOP << std::endl
         << std::endl
         << "version: " << SCENE_VER << std::endl
         << "name: " << m_name << std::endl
         << std::endl
         << SCENE_HEADER_OBJ << std::endl;

    unsigned char i;

    for (const GameObject& obj : objects)
    {
        file << std::endl
             << "name: " << obj.name
             << std::endl
             << "position: " << (obj.position.x / Application::rect_size) << ","
                             << (obj.position.y / Application::rect_size)
             << std::endl
             << "depth: " << obj.depth
             << std::endl
             << "scale: " << obj.scale.x << ","
                          << obj.scale.y
             << std::endl
             << "rotation: " << obj.rotation
             << std::endl
             << "visible: " << obj.visible
             << std::endl
             << "sprite_count: " << obj.sprite_count
             << std::endl
             << "sprite_offsets: ";

        i = 0;
        for (const glm::vec2& ofs : obj.sprite_offsets)
        {
            if (i++) file << ",";
            file << ofs.x / Application::uv_frac.x << ","
                 << ofs.y / Application::uv_frac.y;
        }

        file << std::endl;
    }

    file.close();
}
