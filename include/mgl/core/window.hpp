#ifndef window_hpp
#define window_hpp

#include <iostream>

#include "graphics.hpp"
#include "timer.hpp"
#include "scene.hpp"
#include "inputManager.hpp"
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
        void setActiveScene(std::string);

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
            
        std::string m_activeScene;
        Graphics *m_graphicsInstance;
        Timer *m_timerInstance;
        
        float m_frameRate;
        InputManager *m_inputManager;
        unsigned int m_vao;
        
        bool m_isRunning;

    };
}

#endif