-- asagao/premake5.lua


workspace "Asagao"
    architecture   "x64"
    configurations "Debug"
    platforms      "Windows"

project "Asagao"
    kind       "ConsoleApp"
    language   "C++"
    cppdialect "C++17"

    location  "build"
    targetdir "build/%{cfg.buildcfg}"

    files       { "includes/*.hpp", "source/*.cpp" }
    includedirs { "includes", "libraries/**" }
    libdirs     { "libraries/**" }
    links       { "opengl32", "glad", "glfw3", "gdi32", "imgui" }

    prebuildcommands { "windres -i ../resources/branding/icons.rc -o obj/icons.o" }
    links            { "build/obj/icons.o" }
    
    filter "configurations:Debug"
        symbols "On"
