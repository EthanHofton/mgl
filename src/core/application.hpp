#ifndef application_hpp
#define application_hpp

#include <mgl/mglpch.hpp>
#include "core.hpp"
#include "../events/applicationEvent.hpp"
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

        void onEvent(Event& e);

    private:

        bool onWindowClose(WindowCloseEvent& e);

        // * store a unique pointer to window
        // * beacuse only this class will own the pointer
        std::unique_ptr<Window> m_window;

        // * store weather application is running
        bool m_running = true;
    };

    // * decliration of createApplication to be defined by client
    mgl::Application* createApplication();
}

#endif