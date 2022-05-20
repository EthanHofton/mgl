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

    Entity::Entity(std::string t_entityId)
    {
        m_entityId = t_entityId;
    }
}