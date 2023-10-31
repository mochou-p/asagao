// asagao/includes/interface.hpp


#pragma once


#include "imgui.h"

#include <stdexcept>


class Window;
class Editor;


class Interface
{
public:
    //                                        x     y     w     h
    static inline const auto Home    = ImVec4(0.3f, 0.2f, 0.4f, 0.6f);
    static inline const auto Objects = ImVec4(0.0f, 0.0f, 0.2f, 1.0f);

public:
    Interface(Window& window, Editor& editor);
    ~Interface();

    void init()   const;

    void render() const noexcept;

private:
    Window& r_window;
    Editor& r_editor;
};


[[nodiscard]] inline auto ImVec2_mul_ImVec2(const ImVec2& vector, const ImVec2& multiplier) noexcept
{
    return ImVec2(vector.x * multiplier.x, vector.y * multiplier.y);
}

[[nodiscard]] inline auto ImVec4_div_float(const ImVec4& vector, const float divisor)
{
    if (divisor == 0.0f)
        throw std::runtime_error("cannot divide by 0");

    return ImVec4(vector.x / divisor, vector.y / divisor, vector.z / divisor, vector.w / divisor);
}
