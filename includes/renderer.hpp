// asagao/includes/renderer.hpp


#pragma once


#include "singleton.hpp"


namespace Asagao
{
    class Renderer
    {
    SINGLETON(Renderer)

    public:
        static void init();

        void clear() const;
        void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
        void set_background_color(const v4& color) const;

        f32 zoom = 1.0f;
    private:
        u32 m_id;
    };
}  // Asagao::
