#ifndef keyEvent_hpp
#define keyEvent_hpp

#include "event.hpp"

namespace mgl
{
    // * base key event class all other key events will impliment
    // * stores attrivutes common to all key events
    class KeyEvent : public Event
    {
    public:

        // * function to return the key code of the key event
        inline int getKeyCode() const { return m_keyCode; }

        // * determine the event catogory flags using the macro in event.hpp
        // * impliments the pure virtual function getCategoryFlags()
        EVENT_CLASS_CATEGORY(eventCategoryKeyboard | eventCategoryInput);

    protected:

        // * constructor to set the keycode
        // * protected consturctor so that you cannot make it without a derrived class
        KeyEvent(int t_keycode) : m_keyCode(t_keycode) {}

        // * store the corrisponding event keycode
        int m_keyCode;
    };

    // * event for a key press
    // * inherits from key event
    class KeyPressedEvent : public KeyEvent
    {
    public:

        // * key pressed event constructor
        KeyPressedEvent(int t_keycode, int t_repeteCount) : KeyEvent(t_keycode), m_repeteCount(t_repeteCount) {}

        // * repete count getter
        inline int getRepeteCount() const { return m_repeteCount; }

        // * implimentation of the toString method
        std::string toString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_keyCode << " (" << m_repeteCount << " repeats)";
            return ss.str();
        }

        // * impliments all pure virtual functions
        // * impliments with type as eventType::keyPressed
        // * impliments functions getEventType() and getName() aswell as creating getStaticType()
        EVENT_CLASS_TYPE(keyPressed);

    private:
    
        // * store the ammount the key press was done
        int m_repeteCount;
    };

    // * event for a key release
    // * inherits from key event
    class KeyReleasedEvent : public KeyEvent
    {
    public:

        // * key releaseted event constructor
        KeyReleasedEvent(int t_keycode) : KeyEvent(t_keycode) {}

        // * implimentation of the toString method
        std::string toString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_keyCode;
            return ss.str();
        }

        // * impliments all pure virtual functions
        // * impliments with type as eventType::keyPressed
        // * impliments functions getEventType() and getName() aswell as creating getStaticType()
        EVENT_CLASS_TYPE(keyReleased);
    };
}

#endif