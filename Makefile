CC = c++

CXXFLAGS = -Wall -std=c++17 -stdlib=libc++
CXXFLAGS += -Iinclude/
LDFLAGS = -F lib/SDL2/ -framework SDL2 -rpath "$(shell pwd)"/lib/SDL2/

SRC = $(wildcard src/*.cpp) $(wildcard src/**/*.cpp)
OBJ = $(SRC:.cpp=.o)
PROGRAM = libmgl
BIN = bin

.PHONY: all clean

all: dirs libs $(PROGRAM)

dirs:
	mkdir -p ./$(BIN)

libs:

$(PROGRAM): $(OBJ)
	$(CC) -dynamiclib -o $(BIN)/$(PROGRAM).dylib -install_name @rpath/$(PROGRAM).dylib $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CXXFLAGS) 

clean:
	rm -rf $(BIN) $(OBJ)