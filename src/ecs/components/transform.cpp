#include "transform.hpp"
#include "../entity.hpp"

namespace mgl
{
    glm::vec3 Transform::getPosition(const scope& t_scope) const
    {
        return m_position;    
    }

    void Transform::setPosition(glm::vec3 t_pos)
    {
        if (t_pos == m_position) return;
        m_position = t_pos;
        setUpdate(true);
    }

    void Transform::translate(glm::vec3 t_trans)
    {
        setPosition(m_position + t_trans);
    }

    glm::vec3 Transform::getRotation(const scope& t_scope) const
    {
        return m_rotation;
    }

    void Transform::setRotation(glm::vec3 t_rot)
    {
        if (t_rot == m_rotation) return;
        m_rotation = t_rot;
        setUpdate(true);
    }

    void Transform::rotate(glm::vec3 t_rot)
    {
        setRotation(m_rotation + t_rot);
    }

    glm::vec3 Transform::getScale(const scope& t_scope) const
    {
        return m_scale;
    }

    void Transform::setScale(glm::vec3 t_scale)
    {
        if (t_scale == m_scale) return;
        m_scale = t_scale;
        setUpdate(true);
    }

    void Transform::scale(glm::vec3 t_scale)
    {
        setScale(m_scale * t_scale);
    }

    glm::mat4 Transform::getTransform()
    {
        setUpdate(false);
        if (hasTransformParent())
        {
            return getParentTransform().getTransformNoUpdate() * getTransformNoUpdate();
        }
        else
        {
            return getTransformNoUpdate();
        }

    }

    glm::mat4 Transform::getTransformNoUpdate()
    {
        return glm::translate(glm::mat4(1.0f), m_position)
                * glm::toMat4(glm::quat(m_rotation))
                * glm::scale(glm::mat4(1.0f), m_scale);
    }

    void Transform::setUpdate(bool t_updated)
    {
        m_updated = t_updated;
        if (m_updated && hasTransformParent())
        {
            getParentTransform().setUpdate(true);
        }
    }

    void Transform::setTransformParent(Entity t_parent)
    {
        m_parent = t_parent;
    }
    
    const Entity& Transform::getTransformParent() const 
    {
        return m_parent;
    }

    bool Transform::hasTransformParent() const
    {
        return m_parent.hasComponent<Transform>();
    }

    Transform& Transform::getParentTransform()
    {
        return m_parent.getComponent<Transform>();
    }
}