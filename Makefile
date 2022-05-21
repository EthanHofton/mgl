CC = c++

CXXFLAGS = -Wall -std=c++17 -stdlib=libc++
CXXFLAGS += -Iinclude/ -Isrc/

# macros
CXXFLAGS += -DMGL_PLATFORM_OSX

LDFLAGS = -F lib/SDL2/ -framework SDL2 -rpath "$(shell pwd)"/lib/SDL2/
LDFLAGS += -Llib/glew/lib/ -lGLEW.2.2.0 -rpath "$(shell pwd)"/lib/glew/lib/
LDFLAGS += -framework OpenGL

SRC = $(wildcard src/*.cpp) $(wildcard src/**/*.cpp)
OBJ = $(SRC:.cpp=.o)
PROGRAM = libmgl
BIN = bin

.PHONY: all clean

all: dirs libs $(PROGRAM)

dirs:
	mkdir -p ./$(BIN)

libs:
ifeq ($(wildcard include/GL/.*),)
	@echo "creating include/GL"
	cd lib/glew/auto && make && cd .. && make && make install
	mkdir -p include/GL/
	cp -a lib/glew/include/GL/. include/GL/
endif

$(PROGRAM): $(OBJ)
	$(CC) -dynamiclib -o $(BIN)/$(PROGRAM).dylib -install_name @rpath/$(PROGRAM).dylib $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CXXFLAGS) 

clean:
	rm -rf $(BIN) $(OBJ)