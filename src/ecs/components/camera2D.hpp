#ifndef camera2D_hpp
#define camera2D_hpp

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <mgl/events/event.hpp>
#include <mgl/events/keyEvent.hpp>

namespace mgl
{
    struct Camera2D
    {
        glm::vec3 m_position;
        glm::vec3 m_rotation;
        glm::vec3 m_scale;

        glm::mat4 getView()
        {
            return glm::translate(glm::mat4(1.0f), m_position)
                * glm::toMat4(glm::quat(m_rotation))
                * glm::scale(glm::mat4(1.0f), m_scale);
        }
    };
}

#endif