# asagao/Makefile


APP       := Asagao

BIN       := build
INC       := includes
LIB       := libraries
SRC       := source

GLAD      := $(LIB)\GLAD
GLFW      := $(LIB)\GLFW
GLM       := $(LIB)\GLM
IMGUI     := $(LIB)\IMGUI
STBI      := $(LIB)\STBI

CXX       := g++ -std=c++23
CXXFLAGS  := -O3 -g3 -Wall -Wextra -Werror

SOURCES   := $(GLAD)\src\glad.c $(SRC)\\*.cpp
HEADERS   := -I$(INC) -I$(GLAD)\inc -I$(GLFW)\inc -I$(IMGUI)\inc \
	-I$(STBI)\inc -I$(GLM)\inc
LIBRARIES := -L$(GLFW)\lib -L$(IMGUI)\lib
LINKS     := -lopengl32 -lglfw3 -lgdi32 -limgui

$(APP):
	-@ mkdir $(BIN) 2>nul ||:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(BIN)\$@.exe \
		$(HEADERS) $(LIBRARIES) $(LINKS)

run:
	.\build\$(APP).exe

clean:
	rmdir /S /Q $(BIN)
