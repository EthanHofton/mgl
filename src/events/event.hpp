#ifndef event_hpp
#define event_hpp

#include "../core/core.hpp"
#include <spdlog/fmt/bundled/format.h>

namespace mgl
{
    // * blocking events. Once an event occurs, it is dealed with immidetly
    // * (TODO) create a form of event queue so events can be delt with
    // *    - for exampele once per frame

    enum class eventType
    {
        none = 0,                                                               // * none event
        windowClose, windowResize, windowFocus, windowLostFocus, windowMoved,   // * application event
        appTick, appUpdate, appDraw,                                            // * update event
        keyPressed, keyReleased,                                                // * key event
        mouseButtonPressed, mouseButtonReleased, mouseMoved, mouseScrolled      // * mouse event
    };

    // * catogorys events fit into
    enum eventCategory
    {
        none = 0,
        eventCategoryApplication = BIT(0),
        eventCategoryInput       = BIT(1),
        eventCategoryKeyboard    = BIT(2),
        eventCategoryMouse       = BIT(3),
        eventCategoryMouseButton = BIT(4)
    };

// * macro to impliment all of the pure virtual functions inside of a derrived event class
// * just by providing the event type they are
#define EVENT_CLASS_TYPE(type) static eventType getStaticType() { return eventType::type; } \
                               virtual eventType getEventType() const override { return getStaticType(); } \
                               virtual std::string getName() const override { return #type; }

// * macro to impliment the pure virtual function getCategoryFlags() by providing the category
#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

    // * base event class
    // * to be overrided by other event classes
    class Event
    {
        // * declare EventDispatcher as a friend class
        friend class EventDispatcher;

    public:

        // * pure virtual functions to be implimented
        // * return the type of event the event is
        virtual eventType getEventType() const = 0;
        // * get the name of the event (for debug)
        virtual std::string getName() const = 0;
        // * get the category flags
        virtual int getCategoryFlags() const = 0;
        // * std::to string to print info about the event
        virtual std::string toString() const { return getName(); }

        // * util function to check if an event is in category
        inline bool isInCategory(eventCategory t_category)
        {
            return getCategoryFlags() & t_category;
        }

    protected:

        // * flag to store if the event has been handeled or not
        bool m_handeled = false;
    };

    // * event dispatcher class
    // * used when an event happens, a new instance of the dispatcher is created
    // * and calls the given dispatch function
    class EventDispatcher
    {
        // * store name eventFunction to store a function pointer:
        // *    - return type bool
        // *    - arguments T&
        template<typename T>
        using eventFunction = std::function<bool(T&)>;

    public:

        // * public constructor
        // * takes in referance to an event
        EventDispatcher(Event &t_event) : m_event(t_event) {}

        // * event dispatch function
        // * takes in a call back function of type eventFunction (see above)
        // * returns weather the event was dispatched or not
        template<typename T>
        bool dispatch(eventFunction<T> t_dispatchFunction)
        {
            // * check if the given template arguemnt, T, matches the events type
            if (m_event.getEventType() == T::getStaticType())
            {
                // * set the event handeled flag to the return value of the callback function
                // * call the callback function the the event as the paramenters
                m_event.m_handeled = t_dispatchFunction(*(T*)&m_event);
                // return ture since the event dispatch function was dispatched
                return true;
            }

            // * return false since the event dispatch function was not dispatched
            return false;
        }

    private:

        // * store the reference to the event
        Event &m_event;
    };
}

// * std::cout compatibility
inline std::ostream& operator<<(std::ostream& out, const mgl::Event& e)
{
    out << e.toString();
    return out;
}

// * fmt format string compatibility
template<>
struct fmt::formatter<mgl::Event>
{
    constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) 
    {
        return ctx.end();
    }

    template<typename FormatContext>
    auto format(const mgl::Event& input, FormatContext& ctx) -> decltype(ctx.out())
    {
        return format_to(ctx.out(), "{}", input.toString());
    }
};

#endif