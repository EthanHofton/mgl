#ifndef application_hpp
#define application_hpp

#include <mgl/mglpch.hpp>
#include <mgl/events/applicationEvent.hpp>

#include "layerStack.hpp"
#include "core.hpp"
#include "window.hpp"
#include "timer.hpp"
#include <mgl/imgui/imguiLayer.hpp>
#include <mgl/projection/projection.hpp>
#include <mgl/projection/orthogrphicProjection.hpp>
#include <mgl/projection/perspectiveProjection.hpp>

namespace mgl
{
    enum ProjectionType
    {
        ORTHOGRAPHIC,
        PERSPECTIVE,
    };

    // * application app
    // * controll the main game loop
    class Application
    {
    public:

        // * application constructor and descructor
        Application(ProjectionType t_projectionType);
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

        // * pop a layer onto the layerstack
        void popLayer(Layer* t_layer);
        // * pop an overlay to the layer stack
        void popOverlay(Layer* t_overlay);

        // * get window function
        inline Window& getWindow() { return *m_window; }

        // * get the imgui layer
        inline ImGuiLayer& getImGuiLayer() { return *m_imGuiLayer; }

        // * application getter
        inline static Application& get() { return *s_instance; }

        // * Timer getter
        inline static Timer& getTimer() { return *(s_instance->m_timer); }

        // static void configureCamera();
        // inline static void getCamera() {}

        inline static Projection* getProjection() { return s_instance->m_projection; }

    private:

        bool onWindowClose(WindowCloseEvent& e);

        // * store a unique pointer to window
        // * beacuse only this class will own the pointer
        std::unique_ptr<Window> m_window;

        // * store weather application is running
        bool m_running = true;

        // * layer stack
        LayerStack m_layerStack;

        // * timer
        Timer *m_timer;
        // * store the applications projection
        Projection* m_projection = nullptr;

        // * imgui layer
        ImGuiLayer *m_imGuiLayer;

        // * instance for singleton
        static Application* s_instance;

    };

    // * decliration of createApplication to be defined by client
    mgl::Application* createApplication();
}

#endif