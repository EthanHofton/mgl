CC = c++

CXXFLAGS = -Wall -std=c++17 -stdlib=libc++
CXXFLAGS += -Iinclude/
LDFLAGS = 

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
PROGRAM = libmgl
BIN = bin

.PHONY: all clean

all: dirs libs $(PROGRAM)

dirs:
	mkdir -p ./$(BIN)

libs:

$(PROGRAM): $(OBJ)
	$(CC) -dynamiclib -o $(BIN)/$(PROGRAM).dylib -install_name @rpath/mgl/$(BIN)/$(PROGRAM).dylib $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CXXFLAGS) 

clean:
	rm -rf $(BIN) $(OBJ)