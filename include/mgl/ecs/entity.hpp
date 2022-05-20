#ifndef entity_hpp
#define entity_hpp

#include <iostream>
#include <map>

namespace mgl
{
    class Entity
    {
    public:
        // * static functions to remove entity memory management from the user
        // * reference entity using ids instead of pointers
        // * static create entity function. removes 'new' keyword from user
        template<typename T>
        static void createEntity(std::string t_entityId)
        {
            if (!(std::is_base_of_v<Entity, T>))
            {
                throw std::runtime_error("Given type T is not derrived from Entity");
            }
            s_entites[t_entityId] = new T(t_entityId);
        }
        // * static delete entity function. removed 'delete' keyword from user
        static void deleteEntity(std::string);
        // * static get entity function. stops users from accecing entity by pointers and use ids
        template<typename T>
        static T* getEntity(std::string t_entityId)
        {
            return reinterpret_cast<T*>(s_entites[t_entityId]);
        }

    private:

        // * static map to store all of the entity pointers mapped to there corresponding ids
        static std::map<std::string, Entity*> s_entites;

        // private entity constructor. stoppes the users from using 'new' keyword
        Entity(std::string);
        // private entity constructor. stoppes the users from using 'new' keyword
        virtual ~Entity() = default;

    public:

    private:

        std::string m_entityId;

    };
}

#endif