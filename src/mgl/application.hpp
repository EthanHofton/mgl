#ifndef application_hpp
#define application_hpp

#include "core.hpp"

namespace mgl
{
    // * application app
    // * controll the main game loop
    class Application
    {
    public:

        // * application constructor and descructor
        Application();
        // * application destructor needs to be virtual so it can be overrided
        virtual ~Application();

        // * application main loop
        void run();
    };

    // * decliration of createApplication to be defined by client
    mgl::Application* createApplication();
}

#endif