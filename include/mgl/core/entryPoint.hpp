#ifndef entryPoint_hpp
#define entryPoint_hpp

#include "../util/util.hpp"
#include "window.hpp"

// * external function to be definred by user that creates the main window
// * @returns a pointer to the window created by the user
extern mgl::Window* mgl::createWindow();

// * program entry point
int main(int argc, char **argv);

#endif