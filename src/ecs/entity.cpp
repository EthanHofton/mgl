#include <mgl/ecs/entity.hpp>

namespace mgl
{
    std::map<std::string, Entity*> Entity::s_entites;

    void Entity::deleteEntity(std::string t_entityId)
    {
        auto instance = s_entites.find(t_entityId);
        if (instance != s_entites.end())
        {
            // * call entity on delete
            s_entites[t_entityId]->onDelete();

            delete s_entites[t_entityId];
            s_entites.erase(instance);
        }
    }

    void Entity::deleteAllEntities()
    {
        std::stack<Entity*> deleteStack;
        for (auto entity : s_entites)
        {
            entity.second->onDelete();
            deleteStack.push(entity.second);
        }

        while (!deleteStack.empty())
        {
            delete deleteStack.top();
            deleteStack.pop();
        }

        s_entites.clear();
    }

    std::vector<std::string> Entity::getAllEntites()
    {
        std::vector<std::string> allEntites;
        for (auto entity : s_entites)
        {
            allEntites.push_back(entity.first);
        }

        return allEntites;
    }

    std::vector<std::string> Entity::getAllActiveEntites()
    {
        std::vector<std::string> allEntites;
        for (auto entity : s_entites)
        {
            if (entity.second->isActive())
            {
                allEntites.push_back(entity.first);
            }
        }

        return allEntites;
    }

    Entity::Entity(std::string t_entityId) : m_entityId(t_entityId) {}

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
        m_parent = t_parent;
        if (hasParent())
        {
            getEntity<Entity>(m_parent)->addChild(getEntityId());
        }

        CORE_INFO("entity with id '{}' set entity with id '{}' as parent", m_entityId, m_parent);
    }

    void Entity::activePropagate(bool t_active)
    {
        if (t_active == m_active)
        {
            return;
        }

        m_active = t_active;
        for (auto child : m_children)
        {
            getEntity<Entity>(child)->activePropagate(m_active);
        }
    }

    void Entity::removeChild(std::string t_childId)
    {
        auto instance = std::find(m_children.begin(), m_children.end(), t_childId);
        if (instance != m_children.end())
        {
            m_children.erase(instance);
        }
    }

    std::string Entity::getBaseParent()
    {
        // * (O(n))
        
        if (!hasParent())
        {
            return m_entityId;
        }

        return getEntity<Entity>(m_parent)->getBaseParent();
    }

    std::vector<std::string> Entity::getAncestors()
    {
        if (!hasParent())
        {
            return {};
        }

        std::vector<std::string> v1;
        std::vector<std::string> v2 = getAncestors();
        v1.insert(v1.end(), v2.begin(), v2.end());
        return v1;
    }

    std::vector<std::string> Entity::getDescendantsPreOrder()
    {
        std::vector<std::string> descendants = {getEntityId()};
        for (auto child : m_children)
        {
            std::vector<std::string> v2 = getEntity<Entity>(child)->getDescendantsPreOrder();
            descendants.insert(descendants.end(), v2.begin(), v2.end());
        }

        return descendants;
    }

    std::vector<std::string> Entity::getDescendantsPostOrder()
    {
        std::vector<std::string> descendants = {};
        for (auto child : m_children)
        {
            std::vector<std::string> v2 = getEntity<Entity>(child)->getDescendantsPostOrder();
            descendants.insert(descendants.end(), v2.begin(), v2.end());
        }

        descendants.push_back(getEntityId());

        return descendants;
    }
}