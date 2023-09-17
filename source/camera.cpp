// asagao/source/camera.cpp


#include "camera.hpp"
#include "gtc/matrix_transform.hpp"
#include "window.hpp"
#include "style.hpp"
#include "renderer.hpp"

Camera::Camera()
{
    update_projection();
}

const glm::mat4
Camera::get_mvp(const GameObject& obj)
{
    update_object(&obj);

    return m_projection * m_view * m_model;
}

void
Camera::set_position(const glm::vec3& position)
{
    m_position = position;
}

void
Camera::move(const glm::vec3& delta)
{
    m_position += delta;
}

void
Camera::update_projection()
{
    const glm::vec2 aspect = Window::size * Layout::scene.size * Renderer::zoom;

    m_projection = glm::ortho(-aspect.x, aspect.x, -aspect.y, aspect.y);
}

void
Camera::update_object(const GameObject* obj)
{
    m_view = glm::translate
    (
        mat4_identity,
        m_position - (m_position * obj->depth * 0.08f)
    );

    m_model = glm::translate(mat4_identity, obj->position);
    m_model = glm::rotate(m_model, glm::radians(obj->rotation), z_axis);
    m_model = glm::scale(m_model, obj->scale);
}
