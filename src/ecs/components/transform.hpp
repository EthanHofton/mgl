#ifndef transform_hpp
#define transform_hpp

#include <mgl/mglpch.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace mgl
{
    struct Transform
    {
        glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };
        glm::vec3 m_rotation = { 0.0f, 0.0f, 0.0f };
        glm::vec3 m_scale = { 1.0f, 1.0f, 1.0f };

        glm::mat4 getTransform() const
        {
            return glm::translate(glm::mat4(1.0f), m_position)
                * glm::toMat4(glm::quat(m_rotation))
                * glm::scale(glm::mat4(1.0f), m_scale);
        }
    };
}

#endif