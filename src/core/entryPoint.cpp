#include <mgl/core/entryPoint.hpp>

#include <iostream>

int main(int argc, char** argv)
{
    CORE_INFO("MGL STARTUP");
    mgl::Window *window = mgl::createWindow();

    CORE_INFO("MGL RUNTIME");
    window->run();

    CORE_INFO("MGL CLEANUP");
    delete window;
    window = nullptr;
    
    return EXIT_SUCCESS;
}