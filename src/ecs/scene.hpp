#ifndef scene_hpp
#define scene_hpp

#include <entt/entt.hpp>
#include <mgl/events/event.hpp>

namespace mgl
{
    struct EntityCallbackFunctions
    {
        std::function<void(void*)> getData;
        std::function<int()> getDataSize;
        std::function<int()> getStride;
    };

    class Entity;
    class Scene
    {
    public:

        Scene();
        ~Scene();

        template<typename _componentType>
        void onComponentAdded(Entity *t_entity, _componentType* t_component) {}
        
        void onEvent(Event &e);
        void onUpdate();

        Entity createEntity();
        void destroyEntity(Entity entity);

    private:

        entt::registry m_registery;
        std::map<entt::entity, std::vector<EntityCallbackFunctions>> m_entityGetters;

        friend class Entity;
    };
}

#endif