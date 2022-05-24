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


    };
}

#endif