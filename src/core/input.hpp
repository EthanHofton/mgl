#ifndef input_hpp
#define input_hpp

#include <glm/glm.hpp>

namespace mgl
{
    class Input
    {
    public:

        static inline bool isKeyPressed(int keycode) { return s_instance->isKeyPressedImpl(keycode); }
        static inline bool isKeyReleased(int keycode) { return s_instance->isKeyReleasedImpl(keycode); }

        static inline bool isMouseButtonPressed(int button) { return s_instance->isMouseButtonPressedImpl(button); }
        static inline bool isMouseButtonReleased(int button) { return s_instance->isMouseButtonPressedImpl(button); }

        static inline float getMousePosX() { return s_instance->getMousePosXImpl(); }
        static inline float getMousePosY() { return s_instance->getMousePosYImpl(); }
        static inline glm::vec2 getMousePos() { return s_instance->getMousePosImpl(); }

    protected:

        virtual bool isKeyPressedImpl(int keycode) = 0;
        virtual bool isKeyReleasedImpl(int keycode) = 0;

        virtual bool isMouseButtonPressedImpl(int button) = 0;
        virtual bool isMouseButtonReleasedImpl(int button) = 0;

        virtual float getMousePosXImpl() = 0;
        virtual float getMousePosYImpl() = 0;
        virtual glm::vec2 getMousePosImpl() = 0;

    private:

        static Input* s_instance;
    };
}

#endif