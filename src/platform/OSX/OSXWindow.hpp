#ifndef OSXWindow_hpp
#define OSXWindow_hpp

#ifdef MGL_PLATFORM_OSX

#include <mgl/mglpch.hpp>
#include <mgl/core/window.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace mgl
{
    class OSXWindow : public Window
    {
    public:

        // * OSXWindow constructor
        // * args: windowProps
        OSXWindow(const windowProps&);
        // * virtual distructor
        virtual ~OSXWindow();

        // * on update implimentation
        void onUpdate() override;
        // * get size implimentation
        inline glm::vec2 getSize() const override { return m_data.m_size; }

        // * set event callback function implimentation
        inline void setEventCallback(const eventCallback& t_callback) override { m_data.m_eventCallback = t_callback; }
        // * set vsync function implimentation
        void setVSync(bool t_enabled) override;
        // * check vsync function implimentation
        bool isVSync() const override;

    private:

        // * window initalisztion done here
        virtual void init(const windowProps& t_props);
        // * window cleanup done here
        virtual void quit();

    private:

        // * store pointer to the window created
        GLFWwindow *m_window;

        // * store the window data in a struct
        // * user spicific window data
        struct windowData
        {
            // * store the window title
            std::string m_title;
            // * store the window size
            glm::vec2 m_size;
            // * store weather the window should have vsync enabled
            bool m_vsync;

            // * store the window event callback function
            eventCallback m_eventCallback;
        };

        // * store the classes window data
        windowData m_data;
    };
}

#endif

#endif