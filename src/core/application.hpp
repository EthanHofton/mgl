#ifndef application_hpp
#define application_hpp

#include "core.hpp"
#include "../util/util.hpp"
#include "../events/event.hpp"
#include "window.hpp"

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

    private:

        // * store a unique pointer to window
        // * beacuse only this class will own the pointer
        std::unique_ptr<Window> m_window;

        // * store weather application is running
        bool m_running = ture;
    };

    // * decliration of createApplication to be defined by client
    mgl::Application* createApplication();
}

#endif