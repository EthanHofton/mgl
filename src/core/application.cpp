#include <mgl/mglpch.hpp>
#include <mgl/core/application.hpp>
#include <mgl/events/mouseEvent.hpp>

#include <GL/glew.h>

namespace mgl
{
    Application* Application::s_instance = nullptr;

    Application::Application(ProjectionType t_projectionType)
    {
        MGL_CORE_ASSERT(!s_instance, "Cannot create application twice")
        s_instance = this;

        m_timer = new Timer();

        m_window = std::unique_ptr<Window>(Window::create());
        m_window->setEventCallback(MGL_BIND_FN(Application::onEvent));

        // * disable vsync to lock to custom frame rate
        m_window->setVSync(false);

        switch (t_projectionType)
        {
            case ORTHOGRAPHIC:
                m_projection = new OrthogrphicProjection();
                break;
            case PERSPECTIVE:
                m_projection = new PerspectiveProjection();
                break;
        }
        
        m_imGuiLayer = new ImGuiLayer();
        pushOverlay(m_imGuiLayer);
    }

    Application::~Application()
    {
        delete m_timer;
        if (m_projection != nullptr)
        {
            delete m_projection;
        }
    }

    void Application::pushLayer(Layer* t_layer)
    {
        m_layerStack.pushLayer(t_layer);
    }

    void Application::pushOverlay(Layer* t_overlay)
    {
        m_layerStack.pushOverlay(t_overlay);
    }

    void Application::popLayer(Layer* t_layer)
    {
        m_layerStack.popLayer(t_layer);
    }

    void Application::popOverlay(Layer* t_overlay)
    {
        m_layerStack.popOverlay(t_overlay);
    }

    void Application::onEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(MGL_BIND_FN(Application::onWindowClose));

        if (m_projection != nullptr)
        {
            m_projection->onEvent(e);
        }

        // * propagate the event down the layer stack
        for (auto it = m_layerStack.end(); it != m_layerStack.begin();)
        {
            // * call the on event for each layer
            (*--it)->onEvent(e);
            // * break if the event is handled
            if (e.handeled())
            {
                break;
            }
        }
    }

    void Application::run()
    {
        while (m_running)
        {
            m_timer->tick();

            // * lock to FPS
            if (m_timer->getDeltaTime() >= 1.0 / 120.0)
            {
                m_timer->reset();

                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glClearColor(0, 0, 0, 1);

                // * loop through each layer and call on update
                for (Layer *layer : m_layerStack)
                {
                    layer->onUpdate();
                }

                m_imGuiLayer->begin();
                for (Layer *layer : m_layerStack)
                {
                    layer->onImGuiRender();
                }
                m_imGuiLayer->end();

                m_window->onUpdate();

            }
        }
    }

    bool Application::onWindowClose(WindowCloseEvent& e)
    {
        // * terminate application
        m_running = false;

        // * return true becouse the event has been handled
        return true;
    }
}