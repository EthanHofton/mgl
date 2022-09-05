#include <mgl/mglpch.hpp>
#include "OSXInput.hpp"

#include <GLFW/glfw3.h>
#include <mgl/core/application.hpp>

namespace mgl
{
    Input *Input::s_instance = new OSXInput();

    bool OSXInput::isKeyPressedImpl(int keycode)
    {
        auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
        auto state = glfwGetKey(window, keycode);

        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool OSXInput::isKeyReleasedImpl(int keycode)
    {
        auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
        auto state = glfwGetKey(window, keycode);

        return state == GLFW_RELEASE;
    }


    bool OSXInput::isMouseButtonPressedImpl(int button)
    {
        auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
        auto state = glfwGetMouseButton(window, button);

        return state == GLFW_PRESS;
    }

    bool OSXInput::isMouseButtonReleasedImpl(int button)
    {
        auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
        auto state = glfwGetMouseButton(window, button);

        return state == GLFW_RELEASE;
    }


    float OSXInput::getMousePosXImpl()
    {
        return getMousePosImpl().x;
    }

    float OSXInput::getMousePosYImpl()
    {
        return getMousePosImpl().y;
    }

    glm::vec2 OSXInput::getMousePosImpl()
    {
        auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
        glm::dvec2 pos;
        glfwGetCursorPos(window, &pos.x, &pos.y);

        return {(float)pos.x, (float)pos.y};
    }

}