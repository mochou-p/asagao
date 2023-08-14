# asagao/Makefile


asagao:
	-@ mkdir build 2>nul ||:
# c++23 doesnt exist yet, but g++ allows it for some reason
	g++ -std=c++23 -O3 -g3 -Wall -Wextra -Werror source\main.cpp -o build\$@.exe -Ilibraries\GLFW\inc -Llibraries\GLFW\lib -lopengl32 -lglfw3 -lgdi32

run:
	.\build\asagao.exe

clean:
	rmdir /S /Q build
