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

        // * page on update. gets called once per frame
        inline virtual void update() override {}
        // * page on draw. gets called once per frame
        inline virtual void onDraw() {}
        // * page on event. gets called whenever an event is triggered
        inline virtual void onEvent(SDL_Event &t_e) {}
        // * page on init. gets called right after the constructor
        inline virtual void onInit() {}

        // * get the parent window pointer
        inline Window* getWindow() { return m_parent; }

        void imguiShowSceneHierarchy();

    private:

        // * parent window pointer
        Window *m_parent;

        // * list of all entites pushed to page
    };
}

#endif