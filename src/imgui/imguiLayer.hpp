#ifndef imguiLayer_hpp
#define imguiLayer_hpp

#include <mgl/core/layer.hpp>

namespace mgl
{
    class ImGuiLayer : public Layer
    {
    public:

        ImGuiLayer();
        ~ImGuiLayer();

        void onUpdate() override;
        void onEvent(Event& e) override;
        void onAttach() override;
        void onDetach() override;

    private:

        bool onKeyPressed(KeyPressedEvent& e);
        bool onKeyReleased(KeyReleasedEvent& e);
        bool onMouseButtonPressed(MouseButtonPressedEvent& e);
        bool onMouseButtonReleased(MouseButtonReleasedEvent& e);
        bool onMouseMove(MouseMovedEvent& e);
        bool onMouseScroll(MouseScrolledEvent& e);
    };
}

#endif