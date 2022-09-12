#include <mgl/mglpch.hpp>
#include "imguiLayer.hpp"

#include <imgui/imgui.h>
#include <mgl/platform/OpenGL/imguiOpenGLRenderer.hpp>

#include <mgl/core/keyCodes.hpp>

#include <mgl/core/application.hpp>

namespace mgl
{
    ImGuiLayer::ImGuiLayer() : Layer("ImGui Layer") {}

    ImGuiLayer::~ImGuiLayer() {}

    void ImGuiLayer::onAttach()
    {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        io.KeyMap[ImGuiKey_Tab] = MGL_KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = MGL_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = MGL_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = MGL_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow] = MGL_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = MGL_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown] = MGL_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home] = MGL_KEY_HOME;
        io.KeyMap[ImGuiKey_End] = MGL_KEY_END;
        io.KeyMap[ImGuiKey_Insert] = MGL_KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete] = MGL_KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = MGL_KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] = MGL_KEY_SPACE;
        io.KeyMap[ImGuiKey_Enter] = MGL_KEY_ENTER;
        io.KeyMap[ImGuiKey_Escape] = MGL_KEY_ESCAPE;
        io.KeyMap[ImGuiKey_A] = MGL_KEY_A;
        io.KeyMap[ImGuiKey_C] = MGL_KEY_C;
        io.KeyMap[ImGuiKey_V] = MGL_KEY_V;
        io.KeyMap[ImGuiKey_X] = MGL_KEY_X;
        io.KeyMap[ImGuiKey_Y] = MGL_KEY_Y;
        io.KeyMap[ImGuiKey_Z] = MGL_KEY_Z;

        ImGui::StyleColorsDark();
        ImGui_ImplOpenGL3_Init("#version 410");
    }


    void ImGuiLayer::onDetach()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::onEvent(Event &e)
    {
        EventDispatcher eventDispatcher(e);
        eventDispatcher.dispatch<KeyPressedEvent>(MGL_BIND_FN(ImGuiLayer::onKeyPressed));
        eventDispatcher.dispatch<KeyReleasedEvent>(MGL_BIND_FN(ImGuiLayer::onKeyReleased));
        eventDispatcher.dispatch<KeyTypedEvent>(MGL_BIND_FN(ImGuiLayer::onKeyTyped));
        eventDispatcher.dispatch<MouseButtonPressedEvent>(MGL_BIND_FN(ImGuiLayer::onMouseButtonPressed));
        eventDispatcher.dispatch<MouseButtonReleasedEvent>(MGL_BIND_FN(ImGuiLayer::onMouseButtonReleased));
        eventDispatcher.dispatch<MouseMovedEvent>(MGL_BIND_FN(ImGuiLayer::onMouseMove));
        eventDispatcher.dispatch<MouseScrolledEvent>(MGL_BIND_FN(ImGuiLayer::onMouseScroll));
        eventDispatcher.dispatch<WindowResizeEvent>(MGL_BIND_FN(ImGuiLayer::onWindowResize));
    }

    void ImGuiLayer::begin()
    {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::get();
        io.DisplaySize = ImVec2(app.getWindow().getSize().x, app.getWindow().getSize().y);
        io.DeltaTime = Application::getTimer().getDeltaTime();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::end()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    bool ImGuiLayer::onKeyPressed(KeyPressedEvent& e)
    {
        ImGuiIO &io = ImGui::GetIO();
        io.KeysDown[e.getKeyCode()] = true;

        io.KeyCtrl = io.KeysDown[MGL_KEY_LEFT_CONTROL] || io.KeysDown[MGL_KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[MGL_KEY_LEFT_SHIFT] || io.KeysDown[MGL_KEY_RIGHT_SHIFT];
        io.KeyAlt = io.KeysDown[MGL_KEY_LEFT_ALT] || io.KeysDown[MGL_KEY_RIGHT_ALT];
        io.KeySuper = io.KeysDown[MGL_KEY_LEFT_SUPER] || io.KeysDown[MGL_KEY_RIGHT_SUPER];

        return false;
    }

    bool ImGuiLayer::onKeyReleased(KeyReleasedEvent& e)
    {
        ImGuiIO &io = ImGui::GetIO();
        io.KeysDown[e.getKeyCode()] = false;

        return false;
    }

    bool ImGuiLayer::onKeyTyped(KeyTypedEvent& e)
    {
        ImGuiIO &io = ImGui::GetIO();
        int keycode = e.getKeyCode();
        if (keycode > 0 && keycode < 0x10000)
        {
            io.AddInputCharacter((unsigned short)keycode);
        }

        return true;
    }

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

    bool ImGuiLayer::onWindowResize(WindowResizeEvent& e)
    {
        ImGuiIO &io = ImGui::GetIO();
        io.DisplaySize = ImVec2(e.getSize().x, e.getSize().y);
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

        return false;
    }
}