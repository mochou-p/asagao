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

void
Scene::load(const std::string& name)
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

    // temp
    // expecting that users did not "corrupt" the scene file
    // or atleast kept the same format and logic as Scene::save
    while (!file.eof())
    {
        GameObject obj;

        // name
        std::getline(file, line);
        obj.name = line.substr(line.find(" ") + 1);

        // position
        std::getline(file, line);
        temp = line.substr(line.find(" ") + 1);
        help = temp.find(",");
        obj.position.x  = std::stof(temp.substr(0, help));
        obj.position.y  = std::stof(temp.substr(help + 1));
        obj.position   *= Application::rect_size;

        // depth
        std::getline(file, line);
        obj.depth = std::stof(line.substr(line.find(" ") + 1));

        // scale
        std::getline(file, line);
        temp = line.substr(line.find(" ") + 1);
        help = temp.find(",");
        obj.scale.x = std::stof(temp.substr(0, help));
        obj.scale.y = std::stof(temp.substr(help + 1));
        obj.scale.z = 1.0f;

        // rotation
        std::getline(file, line);
        obj.rotation = std::stof(line.substr(line.find(" ") + 1));

        // visible
        std::getline(file, line);
        obj.visible = std::stoi(line.substr(line.find(" ") + 1));

        // sprite count
        std::getline(file, line);
        obj.sprite_count = std::stoull(line.substr(line.find(" ") + 1));

        // sprite offsets
        std::getline(file, line);
        std::istringstream iss(line.substr(line.find(" ") + 1));
        while (std::getline(iss, temp, ','))
        {
            x = std::stof(temp);
            std::getline(iss, temp, ',');
            y = std::stof(temp);

            obj.sprite_offsets.push_back
            (
                glm::vec2(x, y) * Application::uv_frac
            );
        }

        Application::objects.push_back(obj);

        std::getline(file, line);
    }
}

void
Scene::save(const std::string& name)
{
    std::ofstream file(SCENE_PATH + ("/" + name) + SCENE_EXT);

    if (!file.is_open())
    {
        LOG_ERROR("failed to open " + name);
        return;
    }

    file << SCENE_HEADER_TOP << std::endl
         << std::endl
         << "version: " << SCENE_VER << std::endl
         << "name: " << name << std::endl
         << std::endl
         << SCENE_HEADER_OBJ << std::endl;

    unsigned char i;

    for (const GameObject& obj : Application::objects)
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
