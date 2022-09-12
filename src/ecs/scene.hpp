#ifndef scene_hpp
#define scene_hpp

#include <entt/entt.hpp>
#include "components/transform.hpp"
#include <mgl/events/event.hpp>

namespace mgl
{
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

        friend class Entity;
    };
}

#endif