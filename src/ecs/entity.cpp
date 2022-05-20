#include <mgl/ecs/entity.hpp>

namespace mgl
{
    std::map<std::string, Entity*> Entity::s_entites;

    void Entity::deleteEntity(std::string t_entityId)
    {
        auto instance = s_entites.find(t_entityId);
        if (instance != s_entites.end())
        {
            delete s_entites[t_entityId];
            s_entites.erase(instance);
        }
    }

    void Entity::deleteAllEntities()
    {
        std::stack<Entity*> deleteStack;
        for (auto entity : s_entites)
        {
            deleteStack.push(entity.second);
        }
        s_entites.clear();

        while (!deleteStack.empty())
        {
            delete deleteStack.top();
            deleteStack.pop();
        }
    }

    Entity::Entity(std::string t_entityId)
    {
        m_entityId = t_entityId;
        CORE_INFO("Entity with id '{}' created", m_entityId);
    }

    void Entity::parent(std::string t_parent)
    {
        if (t_parent == m_parent)
        {
            return;
        }

        // * if the entity prevoiusly had a parent
        // *    remove the current entity as a child from prev parent
        if (hasParent())
        {
            getEntity<Entity>(m_parent)->removeChild(getEntityId());
        }

        // assign the entity a new parent
        // if the new parent is not null, add this as a child of the new parent
        // also set the activity of the child to the activiy of the parent
        m_parent = t_parent;
        if (hasParent())
        {
            getEntity<Entity>(m_parent)->addChild(getEntityId());
            active(getEntity<Entity>(m_parent)->isActive());
        }

        CORE_INFO("entity with id '{}' set entity with id '{}' as parent", m_entityId, m_parent);
    }

    void Entity::removeChild(std::string t_childId)
    {
        auto instance = std::find(m_children.begin(), m_children.end(), t_childId);
        if (instance != m_children.end())
        {
            m_children.erase(instance);
        }
    }
}