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
        LayerStack();
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

    private:

        // * store the layer stack
        std::vector<Layer*> m_layers;
        // * store an iterator of where to insert into the layer stack
        std::vector<Layer*>::iterator m_layerInsert;
    };
}

#endif

