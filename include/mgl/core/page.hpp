#ifndef page_hpp
#define page_hpp

#include <map>

#include "graphics.hpp"

namespace mgl
{
    class Window;

    class Page
    {   
    public:

        static std::map<std::string, Page*> s_pages;

    public:

        // * page constructor and destructor
        Page(Window *, std::string);
        virtual ~Page();

        // * page on init. gets called once a page is added to the window
        inline virtual void onInit() {}
        // * page on update. gets called once per frame
        inline virtual void onUpdate() {}
        // * page on draw. gets called once per frame
        inline virtual void onDraw() {}
        // * page on event. gets called whenever an event is triggered
        inline virtual void onEvent(SDL_Event &t_e) {}
        // * page on delete. gets called when page is removed from window
        inline virtual void onDelete() {}

        // * get the page id
        inline std::string getPageId() { return m_pageId; }
        // * get the parent window pointer
        inline Window* getWindow() { return m_parent; }

        // * push entites (TODO)
        // * update entites (TODO)
        // * get intites (TODO)

        void imguiShowSceneHierarchy();

    private:

        // * parent window pointer
        Window *m_parent;
        // * page id
        std::string m_pageId;

        // * list of all entites pushed to page
    };
}

#endif