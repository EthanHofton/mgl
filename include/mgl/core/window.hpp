#ifndef window_hpp
#define window_hpp

#include <iostream>

#include "graphics.hpp"
#include "timer.hpp"
#include "page.hpp"
#include "../util/util.hpp"

namespace mgl
{
    class Window
    {
    public:

        // * window constructpr
        Window(std::string);
        ~Window();
        
        // * window run function (main game loop)
        void run();

        // * set the active page the window is rendering and updating
        void setActivePage(std::string);
        // * add a page via page pointer to the window
        void addPage(Page *);
        // * add a page via page id to the window
        void addPage(std::string);

    private:

        // * ealry update function. run before all other updates    
        void earlyUpdate();
        // * update function. between early and late update
        void update();
        // * late update function. called after update function
        void lateUpdate();
        // * draw function. called after update functions
        void draw();

    private:
            
        Page* m_activePage;
        Graphics *m_graphicsInstance;
        Timer *m_timerInstance;
        
        std::vector<Page*> m_pages;
        
        float m_frameRate;
        // InputManager *m_inputManager;
        unsigned int m_vao;
        
        bool m_isRunning;

    };
}

#endif