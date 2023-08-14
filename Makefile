# asagao/Makefile


BIN := build
LIB := libraries
SRC := source

GLFW := $(LIB)\GLFW

CXX := g++ -std=c++23
CXXFLAGS := -O3 -g3 -Wall -Wextra -Werror

HEADERS := -I$(GLFW)\inc
LIBRARIES := -L$(GLFW)\lib
LINKS := -lopengl32 -lglfw3 -lgdi32

asagao:
	-@ mkdir $(BIN) 2>nul ||:
# c++23 doesnt exist yet, but g++ allows it for some reason
	$(CXX) $(CXXFLAGS) $(SRC)\main.cpp -o $(BIN)\$@.exe $(HEADERS) $(LIBRARIES) $(LINKS)

run:
	.\build\asagao.exe

clean:
	rmdir /S /Q $(BIN)
