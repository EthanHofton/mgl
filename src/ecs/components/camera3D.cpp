#include "camera3D.hpp"
#include <mgl/core/application.hpp>
#include <mgl/core/keyCodes.hpp>
#include <mgl/core/input.hpp>

namespace mgl
{
    Camera3D::Camera3D(float t_moveSpeed, float t_turnSpeed, glm::vec3 t_worldUp) :
            m_moveSpeed(t_moveSpeed), m_turnSpeed(t_turnSpeed), m_wordUp(t_worldUp) 
    {
        m_disabled = false;
        Application::get().getWindow().setRelativeMouseMouse(true);
    }

    bool Camera3D::onMouseMoved(MouseMovedEvent &e)
    {
        if (!m_disabled)
        {
            glm::vec2 mouseRel = e.getDeltaPos();
            mouseRel.x *= m_turnSpeed * Application::getTimer().getDeltaTime();
            mouseRel.y *= m_turnSpeed * Application::getTimer().getDeltaTime();
            
            m_yaw += mouseRel.x;
            m_pitch += mouseRel.y;
            
            if (m_pitch > 89.0f)
            {
                m_pitch = 89.0;
            }
            
            if (m_pitch < -89.0f)
            {
                m_pitch = -89.0;
            }
        }

        return false;
    }

    glm::mat4 Camera3D::getView()
    {
        m_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        m_front.y = sin(glm::radians(m_pitch));
        m_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        m_front = glm::normalize(m_front);
        
        m_right = glm::normalize(glm::cross(m_front, m_wordUp));
        m_up = glm::normalize(glm::cross(m_right, m_front));

        return glm::lookAt(m_camPos, m_camPos + m_front, m_up);
    }

    void Camera3D::onEvent(Event& e)
    {
        EventDispatcher dispatcher(e);

        dispatcher.dispatch<MouseMovedEvent>(MGL_BIND_FN(Camera3D::onMouseMoved));
        dispatcher.dispatch<KeyPressedEvent>(MGL_BIND_FN(Camera3D::onKeyPressed));
    }

    bool Camera3D::onKeyPressed(KeyPressedEvent &e)
    {
        if (e.getKeyCode() == MGL_KEY_ESCAPE)
        {
            if (isDisabled())
            {
                Application::get().getWindow().setRelativeMouseMouse(true);
                enable();
            } else {
                Application::get().getWindow().setRelativeMouseMouse(false);
                disable();
            }
        }

        return false;
    }

    void Camera3D::onUpdate()
    {
        if (Input::isKeyPressed(MGL_KEY_S))
        {
            glm::vec3 trans;
            trans = -m_moveSpeed * m_front * (float)Application::getTimer().getDeltaTime();
            trans.y = 0;
            m_camPos += trans;
        }

        if (Input::isKeyPressed(MGL_KEY_A))
        {
            glm::vec3 trans;
            trans = -m_moveSpeed * m_right * (float)Application::getTimer().getDeltaTime();
            m_camPos += trans;
        }

        if (Input::isKeyPressed(MGL_KEY_D))
        {
            glm::vec3 trans;
            trans = m_moveSpeed * m_right * (float)Application::getTimer().getDeltaTime();
            m_camPos += trans;
        }

        if (Input::isKeyPressed(MGL_KEY_W))
        {
            glm::vec3 trans;
            trans = m_moveSpeed * m_front * (float)Application::getTimer().getDeltaTime();
            trans.y = 0;
            m_camPos += trans;
        }

        if (Input::isKeyPressed(MGL_KEY_SPACE))
        {
            glm::vec3 trans;
            trans = {0, m_moveSpeed * (float)Application::getTimer().getDeltaTime(), 0};
            m_camPos += trans;
        }

        if (Input::isKeyPressed(MGL_KEY_LEFT_SHIFT))
        {
            glm::vec3 trans;
            trans = {0, -m_moveSpeed * (float)Application::getTimer().getDeltaTime(), 0};
            m_camPos += trans;
        }
    }
}