#ifndef inputManager_hpp
#define inputManager_hpp

#include <iostream>
#include <string.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <imgui/imgui.h>
#include <glm/glm.hpp>

#include "graphics.hpp"
#include "../util/util.hpp"

namespace mgl
{
    class InputManager
    {
    public:
        
        enum MOUSE_BUTTONS
        {
            left = 0,
            right,
            middle,
            back,
            forward
        };
        
    public:
        
        static InputManager *instance();
        static void release();
        
    private:
        
        InputManager();
        ~InputManager();
        
    public:
        
        inline bool keyDown(SDL_Scancode t_scancode)
        { return m_keyboardStates[t_scancode] && !(ImGui::GetIO().WantCaptureKeyboard) && !m_disableInput; }
        inline bool keyPressed(SDL_Scancode t_scancode)
        { return m_keyboardStates[t_scancode] && !m_prevKeyState[t_scancode] && !(ImGui::GetIO().WantCaptureKeyboard) && !m_disableInput; }
        inline bool keyReleased(SDL_Scancode t_scancode)
        { return !m_keyboardStates[t_scancode] && m_prevKeyState[t_scancode] && !(ImGui::GetIO().WantCaptureKeyboard) && !m_disableInput; }
        
        bool mouseButtonDown(MOUSE_BUTTONS);
        bool mouseButtonPressed(MOUSE_BUTTONS);
        bool mouseButtonReleased(MOUSE_BUTTONS);

        inline void disableInput(bool t_b) { m_disableInput = t_b; }
        inline bool disableInput() { return m_disableInput; }
        
        inline glm::vec2 getMousePos() { return m_mPos; }
        inline glm::vec2 getDeltaMousePos() { return m_dmPos; }
        
        void giveEvents(SDL_Event);
        inline bool mouseMotion() { return (m_mouseMovement && !(ImGui::GetIO().WantCaptureMouse) && !m_disableInput); }
        inline void mouseMotion(bool t_m) { m_mouseMovement = t_m; }
        
        void update();
        inline void updatePrevInput()
        { memcpy(m_prevKeyState, m_keyboardStates, m_keyLeangh); m_prevMouseState = m_mouseState; }
        
    private:

        Graphics *m_graphics;

        bool m_disableInput;
        
        Uint8 *m_prevKeyState;
        const Uint8 *m_keyboardStates;
        int m_keyLeangh;
        
        Uint32 m_prevMouseState;
        Uint32 m_mouseState;
        
        glm::vec2 m_mPos;
        glm::vec2 m_dmPos;
        
        bool m_mouseMovement;
        bool m_mouseFirst;
        SDL_Event m_event;
        
        static InputManager* s_instance;
    };
}

#endif