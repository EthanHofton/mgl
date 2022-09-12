#ifndef entryPoint_hpp
#define entryPoint_hpp

#ifdef MGL_PLATFORM_OSX

#include <mgl/mglpch.hpp>
#include <mgl/core/application.hpp>

// * define an external function for the clinent to create the main application
extern mgl::Application* mgl::createApplication();

// * main function
// * to be defined in the header file only so it can be copied into the clients app
// * instead of being complied amd linked without explisity knowing createApplication()
int main(int argc, char** argv)
{
    // * define the app using createApplicaion()
    MGL_CORE_INFO("MGL STARTUP");
    auto app = mgl::createApplication();

    // * run the app
    MGL_CORE_INFO("MGL RUNTIME");
    app->run();

    // delete the app
    MGL_CORE_INFO("MGL CLEANUP");
    delete app;
}

#endif

#endif