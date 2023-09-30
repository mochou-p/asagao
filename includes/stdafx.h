// asagao/includes/stdafx.h


#pragma once


// standard library
#include <functional>
#include <map>
#include <memory>
#include <vector>

#include <exception>

#include <filesystem>

#include <iostream>
// #include <format>

#include <fstream>

#include <sstream>
#include <string>
#include <cstring>

#include <chrono>
#include <ctime>


// other libraries
#include "glad/glad.h"

#include "glfw3.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_stdlib.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#include "IconsFontAwesome6.h"


// typedefs
typedef char                   i8;
typedef unsigned char          u8;
typedef short                 i16;
typedef unsigned short        u16;
typedef int                   i32;
typedef unsigned int          u32;
typedef float                 f32;
typedef long long             i64;
typedef unsigned long long    u64;
typedef double                f64;
typedef char*                cstr;
typedef const char*        c_cstr;
typedef std::string           str;
typedef glm::vec2              v2;
typedef glm::vec3              v3;
typedef glm::vec4              v4;
typedef glm::mat4              m4;


// forward declarations
class GameObject;
class VertexArray;
class IndexBuffer;
class Shader;
class Rect;
class VertexBuffer;
class VertexBufferLayout;
class Interface;
