#ifndef entryPoint_hpp
#define entryPoint_hpp

extern mgl::Application* mgl::createApplication();

int main(int argc, char** argv)
{
    auto app = mgl::createApplication();

    app->run();

    delete app;
}

#endif