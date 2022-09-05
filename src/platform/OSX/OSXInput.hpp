#ifndef OSXInput_hpp
#define OSXInput_hpp

#include <mgl/core/input.hpp>

namespace mgl
{
    class OSXInput : public Input
    {
    protected:

        virtual bool isKeyPressedImpl(int keycode) override;
        virtual bool isKeyReleasedImpl(int keycode) override;

        virtual bool isMouseButtonPressedImpl(int button) override;
        virtual bool isMouseButtonReleasedImpl(int button) override;

        virtual float getMousePosXImpl() override;
        virtual float getMousePosYImpl() override;
        virtual glm::vec2 getMousePosImpl() override;
    };
}

#endif