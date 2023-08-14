# asagao/Makefile


BIN       := build
LIB       := libraries
SRC       := source

GLFW      := $(LIB)\GLFW
IMGUI     := $(LIB)\IMGUI

CXX       := g++ -std=c++23
CXXFLAGS  := -O3 -g3 -Wall -Wextra -Werror

HEADERS   := -I$(GLFW)\inc -I$(IMGUI)\inc
LIBRARIES := -L$(GLFW)\lib -L$(IMGUI)\lib
LINKS     := -lopengl32 -lglfw3 -lgdi32 -limgui

asagao:
	-@ mkdir $(BIN) 2>nul ||:
# c++23 doesnt exist yet, but g++ allows it for some reason
	$(CXX) $(CXXFLAGS) $(SRC)\main.cpp -o $(BIN)\$@.exe $(HEADERS) $(LIBRARIES) $(LINKS)

run:
	.\build\asagao.exe

clean:
	rmdir /S /Q $(BIN)
