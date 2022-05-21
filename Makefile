CC = c++

# cxx arguments
CXXFLAGS = -Wall -std=c++17 -stdlib=libc++

# include paths
CXXFLAGS += -Iinclude/

# macros
CXXFLAGS += -DMGL_PLATFORM_OSX

LDFLAGS = -F lib/SDL2/ -framework SDL2 -rpath "$(shell pwd)"/lib/SDL2/
LDFLAGS += -Llib/glew/lib/ -lGLEW.2.2.0 -rpath "$(shell pwd)"/lib/glew/lib/
LDFLAGS += -framework OpenGL

SRC = $(wildcard src/*.cpp) $(wildcard src/**/*.cpp)
OBJ = $(SRC:.cpp=.o)
PROGRAM = mgl
BIN = bin

.PHONY: all clean

all: dirs libs precompile $(PROGRAM)

dirs:
	mkdir -p ./$(BIN)
	mkdir -p include/

libs:
ifeq ($(wildcard include/GL/.*),)
	cd lib/glew/auto && make && cd .. && make && make install
	ln -s -f "$(shell pwd)"/lib/glew/include/GL/ "$(shell pwd)"/include/GL
endif
ifeq ($(wildcard include/spdlog/.*),)
	ln -s -f "$(shell pwd)"/lib/spdlog/include/spdlog/ "$(shell pwd)"/include/spdlog
endif
ifeq ($(wildcard include/rapidjson/.*),)
	ln -s -f "$(shell pwd)"/lib/rapidjson/include/rapidjson "$(shell pwd)"/include/rapidjson
endif
ifeq ($(wildcard include/glm/.*),)
	ln -s -f "$(shell pwd)"/lib/glm/glm "$(shell pwd)"/include/glm
endif
ifeq ($(wildcard include/mgl/.*),)
	ln -s -f "$(shell pwd)"/src/ "$(shell pwd)"/include/mgl
endif

precompile:
ifeq ($(wildcard src/$(PROGRAM)pch.hpp.gch),)
	@echo creating precompile
	$(CC) $(CXXFLAGS) src/$(PROGRAM)pch.hpp
endif

$(PROGRAM): $(OBJ)
	$(CC) -dynamiclib -o $(BIN)/lib$(PROGRAM).dylib -install_name @rpath/lib$(PROGRAM).dylib $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CXXFLAGS) 

clean:
	rm -rf $(BIN) $(OBJ)