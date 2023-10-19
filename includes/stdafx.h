// asagao/includes/stdafx.h


#pragma once


// standard library
#include <functional>
#include <map>
#include <unordered_map>
#include <memory>
#include <vector>
#include <utility>

#include <exception>

#include <filesystem>

#include <iostream>
// c++20: #include <format>

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


// asagao
#include "singleton.hpp"


// typedefs
//                                                            min |                        max
//                                     ---------------------------+---------------------------
typedef char                   i8;  //                       -127 |                        127
typedef unsigned char          u8;  //                          0 |                        255
typedef short                 i16;  //                    -32,768 |                     32,767
typedef unsigned short        u16;  //                          0 |                     65,535
typedef int                   i32;  //             -2,147,483,648 |              2,147,483,647
typedef unsigned int          u32;  //                          0 |              4,294,967,295
typedef long long             i64;  // -9,223,372,036,854,775,808 |  9,223,372,036,854,775,807
typedef unsigned long long    u64;  //                          0 | 18,446,744,073,709,551,615
typedef float                 f32;
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
class TileSetLayer;
