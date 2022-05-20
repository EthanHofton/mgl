#ifndef scence_hpp
#define scence_hpp

#include <vector>

#include "graphics.hpp"
#include "../ecs/entity.hpp"

namespace mgl
{
    class Window;

    // * scence class
    // * scence class inherets from entity
    class Scene : public Entity
    {
    friend class Entity;
    public:

        static std::vector<std::string> s_scenes;

    protected:

        // * page constructor and destructor
        Scene(std::string, Window *);
        virtual ~Scene();

    public:
        
        // * get the parent window pointer
        inline Window* getWindow() { return m_parent; }

        void imguiInspector() override;

    private:

        void imguiChildTree(std::string t_child);

    private:

        // * parent window pointer
        Window *m_parent;
    };
}

#endif