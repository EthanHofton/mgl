#ifndef entity_hpp
#define entity_hpp

#include <iostream>
#include <map>
#include <vector>

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
    // *    - ensure that the first argument of the custructor is the entity id
    class Entity
    {
    public:
        // * static functions to remove entity memory management from the user
        // * reference entity using ids instead of pointers

        // * static create entity function. removes 'new' keyword from user
        template<typename T, typename... Args>
        static T* createEntity(std::string t_entityId, Args... args)
        {
            if (!(std::is_base_of_v<Entity, T>))
            {
                throw std::runtime_error("Given type T is not derrived from Entity");
            }

            if (t_entityId == "")
            {
                throw std::runtime_error("Entity cannot have blank entity id");
            }

            if (s_entites.find(t_entityId) == s_entites.end())
            {
                throw std::runtime_error("Entity ids must be unqiue");
            }

            T* new_e = new T(t_entityId, args...);
            s_entites[t_entityId] = new_e;
            return new_e;
        }

        // * static delete entity function. removed 'delete' keyword from user
        static void deleteEntity(std::string);
        // * static delete all function. this function deletes all remaning entites
        static void deleteAllEntities();

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

        // * return a list with all the ids of all the entites in existence
        static std::vector<std::string> getAllEntites();

    private:

        // * static map to store all of the entity pointers mapped to there corresponding ids
        static std::map<std::string, Entity*> s_entites;

    protected:

        // protected entity constructor. stops the users from using 'new' keyword
        Entity(std::string);
        // protected entity constructor. stops the users from using 'new' keyword
        inline virtual ~Entity() { CORE_INFO("Entity with id '{}' deleted", m_entityId); }

    public:

        // * entity id getter
        inline std::string getEntityId() { return m_entityId; }

        // * entity active getter
        inline bool isActive() { return m_active; }
        // * entity active setter
        inline void active(bool t_active) { m_active = t_active; }
        // * propagte activity to children
        void activePropagate(bool);

        // * entity parent setter
        void parent(std::string);
        // * entity parent getter
        inline std::string getParent() { return m_parent; }
        // * has parent check
        inline bool hasParent() { return (m_parent != ""); }
        // * get base parent
        std::string getBaseParent();

        // * child getter
        inline std::vector<std::string> getChildren() { return m_children; }
        // * has children check
        inline bool hasChildren() { return (!m_children.empty()); }

        // * virutal entity update function
        virtual inline void update() {}

        // * entity appears in imgui inspector
        void imguiInspector();
        // * custom entity imgui properties
        virtual void customImguiInspector() {}

    private:

        inline void addChild(std::string t_childId) { m_children.push_back(t_childId); }
        void removeChild(std::string t_childId);

    private:

        // * store the entity id
        std::string m_entityId;

        // * entity parent
        // * "" = null parent
        std::string m_parent = "";

        // * list of entity children
        std::vector<std::string> m_children;

        // * entity active property
        bool m_active = true;

    };
}

#endif