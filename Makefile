CC = c++

# cxx arguments
CXXFLAGS = -Wall -std=c++17 -stdlib=libc++

# include paths
CXXFLAGS += -Iinclude/

# macros
CXXFLAGS += -DMGL_PLATFORM_OSX
CXXFLAGS += -DMGL_ENABLE_ASSERTS

# dynamicly link to GLEW
LDFLAGS += -Llib/glew/lib/ -lGLEW.2.2.0 -rpath "$(shell pwd)"/lib/glew/lib/
# statically link to glfw
LDFLAGS = -Llib/glfw/bin/src/ -lglfw3
# additional framework dependencies
LDFLAGS += -framework Cocoa -framework OpenGL -framework IOKit

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
	@echo building glew
	cd lib/glew/auto && make && cd .. && make && make install
	@echo creating soft link include/GL
	ln -s -f "$(shell pwd)"/lib/glew/include/GL/ "$(shell pwd)"/include/GL
endif
ifeq ($(wildcard include/spdlog/.*),)
	@echo creating soft link include/spdlog
	ln -s -f "$(shell pwd)"/lib/spdlog/include/spdlog/ "$(shell pwd)"/include/spdlog
endif
ifeq ($(wildcard include/rapidjson/.*),)
	@echo creating soft link include/rapidjson
	ln -s -f "$(shell pwd)"/lib/rapidjson/include/rapidjson "$(shell pwd)"/include/rapidjson
endif
ifeq ($(wildcard include/glm/.*),)
	@echo creating soft link include/glm
	ln -s -f "$(shell pwd)"/lib/glm/glm "$(shell pwd)"/include/glm
endif
ifeq ($(wildcard lib/glfw/bin/.*),)
	@echo building glfw
	cd lib/glfw/ && mkdir bin && cd bin && cmake .. && make all
endif
ifeq ($(wildcard include/glfw/.*),)
	@echo creating soft link include/glfw
	ln -s -f "$(shell pwd)"/lib/glfw/include/GLFW "$(shell pwd)"/include/glfw
endif

ifeq ($(wildcard include/mgl/.*),)
	@echo creating soft link include/mgl
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