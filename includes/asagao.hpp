// asagao/includes/asagao.hpp


#pragma once
#ifndef __asagao_hpp_
#define __asagao_hpp_

#include "application.hpp"
#include "camera.hpp"
#include "renderer.hpp"
#include "window.hpp"
#include "interface.hpp"

namespace Asagao
{
    inline auto& Application = Application::get_instance();
    inline auto& Renderer    =    Renderer::get_instance();
    inline auto& Window      =      Window::get_instance();
    inline auto& Camera      =      Camera::get_instance();
    inline auto& Interface   =   Interface::get_instance();
}  // Asagao

#endif  // __asagao_hpp_
