#include <mgl/mglpch.hpp>
#include "imguiLayer.hpp"

#include <imgui/imgui.h>
#include <mgl/platform/OpenGL/imguiOpenGLRenderer.hpp>
#include <GLFW/glfw3.h>

#include <mgl/core/application.hpp>

namespace mgl
{
    ImGuiLayer::ImGuiLayer() : Layer("ImGui Layer") {}

    ImGuiLayer::~ImGuiLayer() {}

    void ImGuiLayer::onUpdate()
    {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::get();
        io.DisplaySize = ImVec2(app.getWindow().getSize().x, app.getWindow().getSize().y);

        double current_time = glfwGetTime();
        io.DeltaTime = m_time > 0.0 ? (float)(current_time - m_time) : (float)(1.0f / 60.0f);
        m_time = current_time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::onEvent(Event &e)
    {
        EventDispatcher eventDispatcher(e);
        eventDispatcher.dispatch<KeyPressedEvent>(MGL_BIND_FN(ImGuiLayer::onKeyPressed));
        eventDispatcher.dispatch<KeyReleasedEvent>(MGL_BIND_FN(ImGuiLayer::onKeyReleased));
        // eventDispatcher.dispatch<KeyTypedEvent>(MGL_BIND_FN(ImGuiLayer::onKeyTyped));
        eventDispatcher.dispatch<MouseButtonPressedEvent>(MGL_BIND_FN(ImGuiLayer::onMouseButtonPressed));
        eventDispatcher.dispatch<MouseButtonReleasedEvent>(MGL_BIND_FN(ImGuiLayer::onMouseButtonReleased));
        eventDispatcher.dispatch<MouseMovedEvent>(MGL_BIND_FN(ImGuiLayer::onMouseMove));
        eventDispatcher.dispatch<MouseScrolledEvent>(MGL_BIND_FN(ImGuiLayer::onMouseScroll));
        eventDispatcher.dispatch<WindowResizeEvent>(MGL_BIND_FN(ImGuiLayer::onWindowResize));
    }

    bool ImGuiLayer::onKeyPressed(KeyPressedEvent& e)
    {
        return false;
    }

    bool ImGuiLayer::onKeyReleased(KeyReleasedEvent& e)
    {
        return false;
    }

    // bool onKeyTyped(KeyTypedEvent& e)
    // {
    //     return true;
    // }

    bool ImGuiLayer::onMouseButtonPressed(MouseButtonPressedEvent& e)
    {
        ImGuiIO &io = ImGui::GetIO();
        io.MouseDown[e.getMouseButton()] = true;

        return false;
    }

    bool ImGuiLayer::onMouseButtonReleased(MouseButtonReleasedEvent& e)
    {
        ImGuiIO &io = ImGui::GetIO();
        io.MouseDown[e.getMouseButton()] = false;

        return false;
    }

    bool ImGuiLayer::onMouseMove(MouseMovedEvent& e)
    {
        ImGuiIO &io = ImGui::GetIO();
        io.MousePos = ImVec2(e.getPos().x, e.getPos().y);

        return false;
    }

    bool ImGuiLayer::onMouseScroll(MouseScrolledEvent& e)
    {
        ImGuiIO &io = ImGui::GetIO();
        io.MouseWheel += e.getOffset().y;
        io.MouseWheelH += e.getOffset().x;

        return false;
    }

    bool onWindowResize(WindowResizeEvent& e)
    {
        return false;
    }


    void ImGuiLayer::onAttach()
    {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        // * TEMP
        // * should use mgl key code
        io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
        io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
        io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
        io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
        io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
        io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
        io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
        io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
        io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
        io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
        io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::onDetach()
    {

    }
}