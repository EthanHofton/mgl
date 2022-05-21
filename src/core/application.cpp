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

    void Application::run()
    {
        MouseMovedEvent e({256, 321});
        // CORE_INFO("{}", e);
        std::cout << e << std::endl;
        // while (true);
    }
}