// asagao/includes/renderer.hpp


#pragma once

namespace Asagao
{
    class Renderer
    {
    public:
        static Renderer& get_instance()
        {
            static Renderer instance;

            return instance;
        }
    private:
        Renderer() {}

        Renderer           (const Renderer&) = delete;
        Renderer& operator=(const Renderer&) = delete;


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
