#ifndef layer_hpp
#define layer_hpp

#include <mgl/core/core.hpp>
#include <mgl/events/event.hpp>

namespace mgl
{
    // * layer class
    // * used in layer stack
    class Layer
    {
    public:

        // * layer constructor
        // * t_name represents the debug name "layer" for default
        Layer(const std::string& t_name = "Layer");
        // * virtual layer destructor so it can be overriden
        virtual ~Layer();

        // * function called on layer attached to the layer stack, this is called
        virtual void onAttach() {}
        // * function called when layer is detached from the layer stack
        virtual void onDetach() {}
        // * function called on update
        virtual void onUpdate() {}
        // * called when an event is sent to the layer via the event dispatcher
        virtual void onEvent(Event& t_event) {}

        // layer debug name getter
        inline const std::string& getName() { return m_debugName; }

    protected:

        // * store the debug name
        std::string m_debugName;
    };
}

#endif