#ifndef camera3D_hpp
#define camera3D_hpp

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <mgl/events/event.hpp>
#include <mgl/events/keyEvent.hpp>
#include <mgl/events/mouseEvent.hpp>

namespace mgl
{
    struct Camera3D
    {
        Camera3D(float t_moveSpeed = 10.0f, float t_turnSpeed = 10.0f, glm::vec3 t_worldUp = {0,1,0});

        float m_moveSpeed;
        float m_turnSpeed;

        glm::vec3 m_front;
        glm::vec3 m_up;
        glm::vec3 m_right;
        glm::vec3 m_wordUp;
        
        float m_yaw = 90.0f;
        float m_pitch = 0.0f;

        glm::mat4 getView();

        void onEvent(Event& e);
        void onUpdate();
        bool onMouseMoved(MouseMovedEvent &e);
        bool onKeyPressed(KeyPressedEvent &e);
        
        void disable() { m_disabled = true; }
        void enable()  { m_disabled = false; }
        bool isDisabled() { return m_disabled; }

        glm::vec3 m_camPos;

    private:

        bool m_keyDown = false;
        glm::vec3 m_trans = {0,0,0};
        bool m_disabled = false;
    };
}

#endif