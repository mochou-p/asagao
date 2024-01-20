-- asagao/premake5.lua


workspace "Asagao"
    architecture   "x64"
    configurations "Debug"
    platforms      "Linux"

project "Asagao"
    kind         "ConsoleApp"
    language     "C++"
    cppdialect   "C++20"

    location  "build"
    targetdir "%{cfg.location}/%{cfg.system}/%{cfg.architecture}/%{cfg.buildcfg}"

    includedirs "includes"
    files     { "source/*.cpp" }

