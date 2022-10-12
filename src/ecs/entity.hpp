#ifndef entity_hpp
#define entity_hpp

#include <entt/entt.hpp>
#include "scene.hpp"
#include <mgl/mglpch.hpp>
#include <entt/entity/registry.hpp>

namespace mgl
{
    class Renderer;
    class Entity
    {
    public:

        Entity(entt::entity t_entity, Scene *t_scene);
        Entity(const Entity& other) = default;
        Entity() = default;
        
        template<typename _componentType, typename... _args>
        _componentType& addComponent(_args&&... t_args)
        {
            _componentType* component = m_scene->m_registery.emplace<_componentType*>(m_entity, new _componentType(std::forward<_args>(t_args)...));
            m_scene->onComponentAdded<_componentType>(this, component);
            return *component;
        }

        template<typename _componentType, typename... _args>
        _componentType& addDrawableComponent(std::function<void(_componentType*, void*)> t_dataGetter, std::function<int(_componentType*)> t_sizeGetter, std::function<int(_componentType*)> t_strideGetter, _args&&... t_args)
        {
            _componentType* component = m_scene->m_registery.emplace<_componentType*>(m_entity, new _componentType(std::forward<_args>(t_args)...));
            m_scene->onComponentAdded<_componentType>(this, component);

            EntityCallbackFunctions funcs;
            funcs.getData = std::bind(t_dataGetter, component, std::placeholders::_1);
            funcs.getDataSize = std::bind(t_sizeGetter, component);
            funcs.getStride = std::bind(t_strideGetter, component);

            m_scene->m_entityGetters[m_entity].push_back(funcs);
            return *component;
        }

        template<typename _componentType>
        _componentType &getComponent()
        {
            return *m_scene->m_registery.get<_componentType*>(m_entity);
        }

        template<typename _componentType>
        bool hasComponent() const
        {
            return m_scene->m_registery.all_of<_componentType*>(m_entity);
        }
        
        template<typename _componentType>
        void removeComponent()
        {
            m_scene->m_registery.remove<_componentType*>(m_entity);
        }

        Scene *getScene()
        {
            return m_scene;
        }

        operator bool() const { return m_entity != entt::null; }
		operator entt::entity() const { return m_entity; }
		operator uint32_t() const { return (uint32_t)m_entity; }

        bool operator==(const Entity& other) const
		{
			return m_entity == other.m_entity && m_scene == other.m_scene;
		}

		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}

        bool null() const
        {
            return m_entity == entt::null;
        }

    private:

        int getDrawableDataSize();
        void getDrawableData(void* m_data);

        entt::entity m_entity = entt::null;
        Scene *m_scene = nullptr;

        friend class Renderer;
    };
}

#endif