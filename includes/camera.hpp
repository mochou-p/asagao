// asagao/includes/camera.hpp


#pragma once


namespace Asagao
{
    class Camera
    {
    SINGLETON_C(Camera)

    public:
        const m4 get_mvp(const GameObject& obj);
        inline const v2 get_position() const { return {m_position.x, m_position.y}; }

        void set_position(const v3& position);
        void move(const v3& delta);

        void update_projection();
    private:
        void update_object(const GameObject* obj);

        const m4 mat4_identity = m4(1.0f);
        const v3 z_axis        = {0.0f, 0.0f, 1.0f};

        v3 m_position;

        m4 m_projection;
        m4 m_view;
        m4 m_model;
    };
}  // Asagao::
