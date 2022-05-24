#include <mgl/mglpch.hpp>
#include <mgl/core/application.hpp>
#include <mgl/events/mouseEvent.hpp>

#include <GL/glew.h>

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace mgl
{
    Application* Application::s_instance = nullptr;

    Application::Application()
    {
        MGL_CORE_ASSERT(!s_instance, "Cannot create application twice")
        s_instance = this;

        m_window = std::unique_ptr<Window>(Window::create());
        m_window->setEventCallback(BIND_EVENT_FN(onEvent));
    }

    Application::~Application()
    {

    }

    void Application::pushLayer(Layer* t_layer)
    {
        m_layerStack.pushLayer(t_layer);
    }

    void Application::pushOverlay(Layer* t_overlay)
    {
        m_layerStack.pushOverlay(t_overlay);
    }

    void Application::onEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

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
            glClearColor(0, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // * loop through each layer and call on update
            for (Layer *layer : m_layerStack)
            {
                layer->onUpdate();
            }

            m_window->onUpdate();
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