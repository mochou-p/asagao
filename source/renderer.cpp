// asagao/source/renderer.cpp


#include "stdafx.h"

#include "asagao.hpp"

#include "renderer.hpp"
#include "log.hpp"
#include "shader.hpp"
#include "vertex_array.hpp"
#include "index_buffer.hpp"
#include "rect.hpp"
#include "game_object.hpp"


static void load_opengl_functions();
static void render();

static void GLAPIENTRY debug_message_callback(u32 source, u32 type, u32 id, u32 severity, i32 length, c_cstr message, const void* param);


namespace Asagao
{
    void
    Renderer::init()
    {
        load_opengl_functions();

        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(debug_message_callback, nullptr);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);

        glActiveTexture(GL_TEXTURE0);
    }

    void
    Renderer::clear() const
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void
    Renderer::draw
    (const GameObject& obj) const
    {
        static u32 animation_time;
        
        animation_time = Window.get_time() * Application.animation_speed;

        Application.shader->set_mat4("u_mvp",     Camera.get_mvp(obj));
        Application.shader->set_vec2("u_tile_uv", obj.get_uv(animation_time));

        render();
    }

    void
    Renderer::set_background_color
    (const v4& color) const
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }
}  // Asagao::


static void
load_opengl_functions()
{
    assert(gladLoadGLLoader((GLADloadproc) glfwGetProcAddress));

    LOG_INFO(str("OpenGL ") + (c_cstr) glGetString(GL_VERSION));
}

static void GLAPIENTRY
debug_message_callback
(u32 source, u32 type, u32 id, u32 severity, i32 length, c_cstr message, const void* param)
{
    LOG_AUTO(severity, message);
}

static void
render()
{
    glDrawElements(GL_TRIANGLES, INDEX_COUNT, GL_UNSIGNED_INT, nullptr);
}
