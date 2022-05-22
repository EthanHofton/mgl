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
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            m_window->onUpdate();
        }
    }
}