#ifndef layerStack_hpp
#define layerStack_hpp

#include <mgl/mglpch.hpp>
#include <mgl/core/core.hpp>

#include "layer.hpp"

namespace mgl
{
    // * layer stack class
    // * store a vector of layers
    class LayerStack
    {
    public:

        // * layer stack constructor and destructor
        LayerStack() = default;
        ~LayerStack();

        // * push a layer to the layerstack
        void pushLayer(Layer* t_layer);
        // * push an overlay to the layer stack
        // * overlays always go ontop of the last layer
        void pushOverlay(Layer* t_overlay);
        // * remove a layer from the layer stack
        void popLayer(Layer* t_layer);
        // * remove an overlay from the layer stack
        void popOverlay(Layer* t_overlay);

        // get an iterator to the front of the layer stack
        std::vector<Layer*>::iterator begin() { return m_layers.begin(); }
        // get an reverse iterator to the front of the layer stack
        std::vector<Layer*>::iterator end() { return m_layers.end(); }

        std::vector<Layer*>::reverse_iterator rbegin() { return m_layers.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return m_layers.rend(); }

        std::vector<Layer*>::const_iterator begin() const { return m_layers.begin(); }
		std::vector<Layer*>::const_iterator end()	const { return m_layers.end(); }
		std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_layers.rbegin(); }
		std::vector<Layer*>::const_reverse_iterator rend() const { return m_layers.rend(); }

    private:

        // * store the layer stack
        std::vector<Layer*> m_layers;
        // * store an iterator of where to insert into the layer stack
        unsigned int m_layerInsertIndex = 0;
    };
}

#endif

