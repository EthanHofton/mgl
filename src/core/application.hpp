#ifndef application_hpp
#define application_hpp

#include <mgl/mglpch.hpp>
#include <mgl/events/applicationEvent.hpp>
#include "layerStack.hpp"
#include "core.hpp"
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

        // * event handler for application
        // * gets called by window by setting it as the event callback function
        void onEvent(Event& e);

        // * push a layer onto the layerstack
        void pushLayer(Layer* t_layer);
        // * push an overlay to the layer stack
        void pushOverlay(Layer* t_overlay);

    private:

        bool onWindowClose(WindowCloseEvent& e);

        // * store a unique pointer to window
        // * beacuse only this class will own the pointer
        std::unique_ptr<Window> m_window;

        // * store weather application is running
        bool m_running = true;

        // * layer stack
        LayerStack m_layerStack;
    };

    // * decliration of createApplication to be defined by client
    mgl::Application* createApplication();
}

#endif