#include <mgl/core/application.hpp>
#include <mgl/events/mouseEvent.hpp>

namespace mgl
{
    Application::Application()
    {

    }

    Application::~Application()
    {

    }

    bool testDispatchFunction(MouseMovedEvent& e)
    {
        std::cout << e << std::endl;
    }

    void Application::run()
    {
        MouseMovedEvent e({256, 321});
        EventDispatcher ed(e);

        ed.dispatch<MouseMovedEvent>(testDispatchFunction);
        // while (true);
    }
}