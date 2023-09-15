-- asagao/premake5.lua


workspace "Asagao"
    configurations { "Debug" }
    platforms      { "Windows" }

project "Asagao"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir "build/%{cfg.buildcfg}"

    files       { "includes/*.hpp", "source/*.cpp" }
    includedirs { "includes", "libraries/**" }
    libdirs     { "libraries/**" }
    links       { "opengl32", "glad", "glfw3", "gdi32", "imgui" }
        
    filter "configurations:Debug"
        symbols "On"
