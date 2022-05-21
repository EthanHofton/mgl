#ifndef application_hpp
#define application_hpp

extern mgl::Application* mgl::createApplication();

int main(int argc, char** argv)
{
    auto app = createApplication();

    app->run();

    delete app;
}

#endif