#ifndef transform_hpp
#define transform_hpp

#include <mgl/mglpch.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include <mgl/ecs/entity.hpp>

namespace mgl
{
    enum scope
    {
        LOCAL,
        WORLD,
    };

    struct Transform
    {
        glm::vec3 getPosition(const scope& t_scope = WORLD) const;
        void setPosition(glm::vec3 t_pos);
        void translate(glm::vec3 t_trans);

        glm::vec3 getRotation(const scope& t_scope = WORLD) const;
        void setRotation(glm::vec3 t_rot);
        void rotate(glm::vec3 t_rot);

        glm::vec3 getScale(const scope& t_scope = WORLD) const;
        void setScale(glm::vec3 t_scale);
        void scale(glm::vec3 t_scale);

        void setTransformParent(Entity t_parent);
        const Entity& getTransformParent() const;
        bool hasTransformParent() const;

        glm::mat4 getTransform();

        inline bool updated() { return m_updated; }

    private:

        void setUpdate(bool t_updated);
        glm::mat4 getTransformNoUpdate();
        Transform& getParentTransform();

        glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };
        glm::vec3 m_rotation = { 0.0f, 0.0f, 0.0f };
        glm::vec3 m_scale = { 1.0f, 1.0f, 1.0f };

        Entity m_parent;
        std::vector<Transform*> m_children;

        bool m_updated = false;
    };
}

#endif