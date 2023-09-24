// asagao/includes/asagao.hpp


#pragma once

#include "application.hpp"
#include "camera.hpp"
#include "renderer.hpp"
#include "window.hpp"
#include "interface.hpp"

// somehow prevents a crash rn (later in pch.h)
#include <iostream>

namespace Asagao
{
    inline auto& Application = Application::get_instance();
    inline auto& Renderer    =    Renderer::get_instance();
    inline auto& Window      =      Window::get_instance();
    inline auto& Camera      =      Camera::get_instance();
    inline auto& Interface   =   Interface::get_instance();
}  // Asagao::
