#ifndef applicationEvent_hpp
#define applicationEvent_hpp

#include <mgl/mglpch.hpp>
#include "event.hpp"

namespace mgl
{
    // * implimentation for window resize event
    // * derrived from base class event
    class WindowResizeEvent : public Event
    {
    public:

        // * public constructor
        // * takes in the new size of the window
        WindowResizeEvent(glm::vec2 t_size) : m_size(t_size) {}

        // * getter for the new size of the window
        inline glm::vec2 getSize() const { return m_size; } 

        // * to string function implimentation
        std::string toString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: {" << m_size.x << ", " << m_size.y << "}";
            return ss.str();
        }

        // * impliments all pure virtual functions
        // * impliments with type as eventType::keyPressed
        // * impliments functions getEventType() and getName() aswell as creating getStaticType()
        EVENT_CLASS_TYPE(windowResize);
        // * determine the event catogory flags using the macro in event.hpp
        // * impliments the pure virtual function getCategoryFlags()
        EVENT_CLASS_CATEGORY(eventCategoryApplication);

    private:

        // * store the new size of the window
        glm::vec2 m_size;
    };

    // * implimentation for window close event
    // * derrived from base class event
    class WindowCloseEvent : public Event
    {
    public:

        // * public constructor
        WindowCloseEvent() {}

        // * impliments all pure virtual functions
        // * impliments with type as eventType::keyPressed
        // * impliments functions getEventType() and getName() aswell as creating getStaticType()
        EVENT_CLASS_TYPE(windowClose);
        // * determine the event catogory flags using the macro in event.hpp
        // * impliments the pure virtual function getCategoryFlags()
        EVENT_CLASS_CATEGORY(eventCategoryApplication); 
    };

    // * implimentation for app tick event
    // * derrived from base class event
    class AppTickEvent : public Event
    {
    public:

        // * public constructor
        AppTickEvent() {}

        // * impliments all pure virtual functions
        // * impliments with type as eventType::keyPressed
        // * impliments functions getEventType() and getName() aswell as creating getStaticType()
        EVENT_CLASS_TYPE(appTick);
        // * determine the event catogory flags using the macro in event.hpp
        // * impliments the pure virtual function getCategoryFlags()
        EVENT_CLASS_CATEGORY(eventCategoryApplication); 
    };

    // * implimentation for app update event
    // * derrived from base class event
    class AppUpdateEvent : public Event
    {
    public:

        // * public constructor
        AppUpdateEvent() {}

        // * impliments all pure virtual functions
        // * impliments with type as eventType::keyPressed
        // * impliments functions getEventType() and getName() aswell as creating getStaticType()
        EVENT_CLASS_TYPE(appUpdate);
        // * determine the event catogory flags using the macro in event.hpp
        // * impliments the pure virtual function getCategoryFlags()
        EVENT_CLASS_CATEGORY(eventCategoryApplication); 
    };

    // * implimentation for app draw event
    // * derrived from base class event
    class AppDrawEvent : public Event
    {
    public:

        // * public constructor
        AppDrawEvent() {}

        // * impliments all pure virtual functions
        // * impliments with type as eventType::keyPressed
        // * impliments functions getEventType() and getName() aswell as creating getStaticType()
        EVENT_CLASS_TYPE(appDraw);
        // * determine the event catogory flags using the macro in event.hpp
        // * impliments the pure virtual function getCategoryFlags()
        EVENT_CLASS_CATEGORY(eventCategoryApplication); 
    };
}

#endif