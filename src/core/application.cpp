#include <mgl/mglpch.hpp>
#include <mgl/core/application.hpp>
#include <mgl/events/mouseEvent.hpp>

namespace mgl
{
    Application::Application()
    {
        m_window = std::unique_ptr<Window>(Window::create());
    }

    Application::~Application()
    {

    }

    void Application::run()
    {
        while (m_running)
        {
            m_window->onUpdate();
        }
    }
}