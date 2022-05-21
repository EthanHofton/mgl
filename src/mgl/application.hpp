#ifndef application_hpp
#define application_hpp

namespace mgl
{
    class Application
    {
    public:

        Application();
        virtual ~Application();

        void run();
    };

    mgl::Application* createApplication();
}

#endif