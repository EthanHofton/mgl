#include <mgl/mglpch.hpp>
#include <mgl/core/application.hpp>
#include <mgl/events/mouseEvent.hpp>

namespace mgl
{

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application::Application()
    {
        m_window = std::unique_ptr<Window>(Window::create());
        m_window->setEventCallback(BIND_EVENT_FN(onEvent));
    }

    Application::~Application()
    {

    }

    void Application::onEvent(Event& e)
    {
        MGL_CORE_INFO("{}", e);
    }

    void Application::run()
    {
        while (m_running)
        {
            m_window->onUpdate();
        }
    }
}