#ifndef entity_hpp
#define entity_hpp

#include <iostream>
#include <map>

#include "../util/util.hpp"

namespace mgl
{
    // * entity class
    // * to create a new entity use Entity::createEntity<>
    // * to delete an entity use Entity::deleteEntity<>
    // * also use createEntity and deleteEntity when creating an deleting a derrived entity
    // * when creating derrived entity class ensure to:
    // *    - make the construcor and destructor private or protected (private for finial class)
    // *    - add the line 'friend class Entity' as the first line of the class defintion
    class Entity
    {
    public:
        // * static functions to remove entity memory management from the user
        // * reference entity using ids instead of pointers

        // * static create entity function. removes 'new' keyword from user
        template<typename T>
        static T* createEntity(std::string t_entityId)
        {
            if (!(std::is_base_of_v<Entity, T>))
            {
                throw std::runtime_error("Given type T is not derrived from Entity");
            }
            T* new_e = new T(t_entityId);
            s_entites[t_entityId] = new_e;
            return new_e;
        }

        // * static delete entity function. removed 'delete' keyword from user
        static void deleteEntity(std::string);
        
        // * static get entity function. stops users from accecing entity by pointers and use ids
        template<typename T>
        static T* getEntity(std::string t_entityId)
        {
            if (!(std::is_base_of_v<Entity, T>))
            {
                throw std::runtime_error("Given type T is not derrived from Entity");
            }
            return reinterpret_cast<T*>(s_entites[t_entityId]);
        }

    private:

        // * static map to store all of the entity pointers mapped to there corresponding ids
        static std::map<std::string, Entity*> s_entites;

    protected:

        // protected entity constructor. stops the users from using 'new' keyword
        Entity(std::string);
        // protected entity constructor. stops the users from using 'new' keyword
        inline virtual ~Entity() { CORE_INFO("Entity with id '{}' deleted", m_entityId); }

    public:

        inline std::string getEntityId() { return m_entityId; }

    private:

        std::string m_entityId;

    };
}

#endif