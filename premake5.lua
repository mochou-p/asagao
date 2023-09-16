-- asagao/premake5.lua


workspace "Asagao"
    architecture   "x64"
    configurations { "Debug" }
    platforms      { "Windows" }

project "Asagao"
    kind       "ConsoleApp"
    icon       "resources/branding/asagao-icon.ico"
    language   "C++"
    cppdialect "C++17"

    targetdir "build/%{cfg.buildcfg}"

    files       { "includes/*.hpp", "source/*.cpp", "resources/branding/icons/icon.res" }
    includedirs { "includes", "libraries/**" }
    libdirs     { "libraries/**" }
    links       { "opengl32", "glad", "glfw3", "gdi32", "imgui" }

    filter "configurations:Debug"
        symbols "On"
