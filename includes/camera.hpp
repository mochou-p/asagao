// asagao/includes/camera.hpp


#pragma once
#ifndef __camera_hpp_
#define __camera_hpp_

#include "glm.hpp"
#include "game_object.hpp"

class Camera
{
public:
    Camera();
    ~Camera() {};

    inline const glm::mat4 get_mvp() const { return m_proj * m_view * m_model; }

    void set_position(const glm::vec3& position);
    void move(const glm::vec3& delta);

    void update_projection();
    // update_object means update view and model for Camera,
    // because Asagao uses GameObject::depth for view multiplier
    void update_object(const GameObject& obj);
private:
    static inline const glm::mat4 mat4_identity = glm::mat4(1.0f);
    static inline const glm::vec3 z_axis        = {0.0f, 0.0f, 1.0f};

    glm::vec3 m_position;

    glm::mat4 m_proj;
    glm::mat4 m_view;
    glm::mat4 m_model;
};

#endif  // __camera_hpp_