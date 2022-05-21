#ifndef mouseEvent_hpp
#define mouseEvent_hpp

#include "event.hpp"

namespace mgl
{
    // * mouse moved event implimentation
    // * derrived from Event class
    class MouseMovedEvent : public Event
    {
    public:

        // * public constrcutor passing in the mouse possition
        MouseMovedEvent(glm::vec2 t_pos) : m_pos(t_pos) {}

        // * event mouse position getter
        inline glm::vec2 getPos() const { return m_pos; }

        // * to string implimenation
        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: {" << m_pos.x << ", " << m_pos.y << "}";
            return ss.str();
        }

        // * impliments all pure virtual functions
        // * impliments with type as eventType::keyPressed
        // * impliments functions getEventType() and getName() aswell as creating getStaticType()
        EVENT_CLASS_TYPE(mouseMoved);
        // * determine the event catogory flags using the macro in event.hpp
        // * impliments the pure virtual function getCategoryFlags()
        EVENT_CLASS_CATEGORY(eventCategoryMouse | eventCategoryInput);

    private:

        // * store the event mouse pos
        glm::vec2 m_pos;
    };

    // * MouseScrolledEvent implimentation
    // * derrived from Event base class
    class MouseScrolledEvent : public Event
    {
    public:

        // * public construcor
        // * pass in the x and y scroll offset
        MouseScrolledEvent(glm::vec2 t_offset) : m_offset(t_offset) {}

        // * getter of the mouse scroll x,y offset
        inline glm::vec2 getOffset() const { return m_offset; }

        // * to string implimentation
        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: {" << m_offset.x << ", " << m_offset.y << "}";
            return ss.str();
        }

        // * impliments all pure virtual functions
        // * impliments with type as eventType::keyPressed
        // * impliments functions getEventType() and getName() aswell as creating getStaticType()
        EVENT_CLASS_TYPE(mouseScrolled);
        // * determine the event catogory flags using the macro in event.hpp
        // * impliments the pure virtual function getCategoryFlags()
        EVENT_CLASS_CATEGORY(eventCategoryMouse | eventCategoryInput);

    private:

        // * store the mouse scroll event x,y offset
        glm::vec2 m_offset;
    };

    // * mouse button event base class
    // * to be derrived by mouse button pressed and mouse button released
    class MouseButtonEvent : public Event
    {
    public:

        // * getter for mouse button type
        inline int getMouseButton() const { return m_button; }

        // * determine the event catogory flags using the macro in event.hpp
        // * impliments the pure virtual function getCategoryFlags()
        EVENT_CLASS_CATEGORY(eventCategoryMouse | eventCategoryMouseButton | eventCategoryInput);

    protected:

        // * protected custructor so only derrived classes can be instansiated
        // * takes in the type of mouse button
        MouseButtonEvent(int t_button) : m_button(t_button) {}

        // * store the type of mouse button pressed
        int m_button;
    };

    // * mouse button pressed event class
    // * derrived from mouse button event base class
    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:

        // * mouse button pressed event construcor
        MouseButtonPressedEvent(int t_button) : MouseButtonEvent(t_button) {}

        // * mouse button pressed event to string
        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_button;
            return ss.str();
        }

        // * impliments all pure virtual functions
        // * impliments with type as eventType::keyPressed
        // * impliments functions getEventType() and getName() aswell as creating getStaticType()
        EVENT_CLASS_TYPE(mouseButtonPressed);
    };

    // * mouse button released event class
    // * derrived from mouse button event base class
    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:

        // * mouse button released event construcor
        MouseButtonReleasedEvent(int t_button) : MouseButtonEvent(t_button) {}

        // * mouse button released event to string
        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << m_button;
            return ss.str();
        }

        // * impliments all pure virtual functions
        // * impliments with type as eventType::keyPressed
        // * impliments functions getEventType() and getName() aswell as creating getStaticType()
        EVENT_CLASS_TYPE(mouseButtonReleased);
    };
}

#endif