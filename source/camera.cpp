// asagao/source/camera.cpp


#include "stdafx.h"

#include "asagao.hpp"

#include "camera.hpp"
#include "game_object.hpp"
#include "style.hpp"


namespace Asagao
{
    Camera::Camera()
    {
        update_projection();
    }

    const m4
    Camera::get_mvp
    (const GameObject& obj)
    {
        update_object(&obj);

        return m_projection * m_view * m_model;
    }

    void
    Camera::set_position
    (const v3& position)
    {
        m_position = position;
    }

    void
    Camera::move
    (const v3& delta)
    {
        m_position += delta;
    }

    void
    Camera::update_projection()
    {
        const v2 aspect = Window.size * Layout::scene.size * Renderer.zoom;

        m_projection = glm::ortho(-aspect.x, aspect.x, -aspect.y, aspect.y);
    }

    void
    Camera::update_object
    (const GameObject* obj)
    {
        m_view  = glm::translate(mat4_identity, m_position - (m_position * obj->depth * 0.08f));
        //                                                                       temp ^^^^^^^

        m_model = glm::translate(mat4_identity, obj->position);
        m_model = glm::rotate(m_model, glm::radians(obj->rotation), z_axis);
        m_model = glm::scale(m_model, obj->scale);
    }
}  // Asagao::
