// asagao/includes/camera.hpp


#pragma once
#ifndef __camera_hpp_
#define __camera_hpp_

#include "glm.hpp"

class GameObject;

namespace Asagao
{
    class Camera
    {
    public:
        static Camera& get_instance()
        {
            static Camera instance;

            return instance;
        }
    private:
        Camera();

        Camera           (const Camera&) = delete;
        Camera& operator=(const Camera&) = delete;


    public:
        const glm::mat4 get_mvp(const GameObject& obj);
        inline const glm::vec2 get_position() const { return {m_position.x, m_position.y}; }

        void set_position(const glm::vec3& position);
        void move(const glm::vec3& delta);

        void update_projection();
    private:
        void update_object(const GameObject* obj);

        const glm::mat4 mat4_identity = glm::mat4(1.0f);
        const glm::vec3 z_axis        = {0.0f, 0.0f, 1.0f};

        glm::vec3 m_position;

        glm::mat4 m_projection;
        glm::mat4 m_view;
        glm::mat4 m_model;
    };
}  // Asagao::

#endif  // __camera_hpp_
