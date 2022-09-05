#ifndef window_hpp
#define window_hpp

#include <mgl/mglpch.hpp>
#include <mgl/events/event.hpp>
#include "core.hpp"

namespace mgl
{
    // * struct to store all window properties
    struct windowProps
    {
        // * store the window title
        std::string m_title;
        // * store the window size
        glm::vec2 m_size;

        // * window properties constructor
        // * defualt args:
        // *    - window title: "untitled project"
        // *    - window size: {1280px, 620px}
        windowProps(const std::string& t_title = "untitled project", glm::vec2 t_size = {1280, 620}) : 
        m_title(t_title), m_size(t_size) {}
    };

    // * window class
    // * all pure virtual function (interfance)
    // * window class must be implimented per platform
    // * this abstracts the patform away
    class Window
    {
    public:

        // * store event callback function
        // * function properties:
        // *    - returns void
        // *    - param Event&
        using eventCallback = std::function<void(Event&)>;

        // * define virtual window construor for inheritance
        virtual ~Window() {}

        // * pure virutal onupdate function
        virtual void onUpdate() = 0;
        // * pure virutal getSize function
        virtual glm::vec2 getSize() const = 0;

        // * window attribute functions
        // * set the window event callback function
        virtual void setEventCallback(const eventCallback& t_callback) = 0;
        // * set if the window uses vsync (cap fps)
        virtual void setVSync(bool t_enabled) = 0;
        // * check if the window is using vsync
        virtual bool isVSync() const = 0;

        // * get the native window from the pre platform implamentation
        virtual void* getNativeWindow() const = 0;

        // * create function must be implimented per platform
        static Window* create(const windowProps& t_props = windowProps());
    };
}

#endif