#include <mgl/mglpch.hpp>
#include "imguiLayer.hpp"

#include <imgui/imgui.h>
#include <mgl/platform/OpenGL/imguiOpenGLRenderer.hpp>
#include <glfw/glfw3.h>

namespace mgl
{
    ImGuiLayer::ImGuiLayer() : Layer("ImGui Layer")
    {

    }

    ImGuiLayer::~ImGuiLayer()
    {
        
    }

    void ImGuiLayer::onUpdate()
    {

    }

    void ImGuiLayer::onEvent(Event &e)
    {
        
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
        io.KeyMap[ImGuiKey_] = GLFW_KEY_;
        io.KeyMap[ImGuiKey_] = GLFW_KEY_;
        io.KeyMap[ImGuiKey_] = GLFW_KEY_;
        io.KeyMap[ImGuiKey_] = GLFW_KEY_;
        io.KeyMap[ImGuiKey_] = GLFW_KEY_;
        io.KeyMap[ImGuiKey_] = GLFW_KEY_;
        io.KeyMap[ImGuiKey_] = GLFW_KEY_;
        io.KeyMap[ImGuiKey_] = GLFW_KEY_;
        io.KeyMap[ImGuiKey_] = GLFW_KEY_;
        io.KeyMap[ImGuiKey_] = GLFW_KEY_;
        io.KeyMap[ImGuiKey_] = GLFW_KEY_;
    }

    void ImGuiLayer::onDetach()
    {

    }
}