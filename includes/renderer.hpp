// asagao/includes/renderer.hpp


#pragma once

#include "vertex_array.hpp"
#include "index_buffer.hpp"
#include "shader.hpp"
#include "glm.hpp"

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
        void draw(const VertexArray& va, const IndexBuffer& ib,
            const Shader& shader) const;
        void set_background_color(const glm::vec4& color) const;

        float zoom = 1.0f;
    private:
        unsigned int m_id;
    };
}  // Asagao::
