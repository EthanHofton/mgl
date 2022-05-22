#include "layerStack.hpp"

namespace mgl
{
    LayerStack::LayerStack()
    {
        m_layerInsert = m_layers.begin();
    }

    LayerStack::~LayerStack()
    {
        for (Layer* layer : m_layers)
        {
            delete layer;
        }
    }

    void LayerStack::pushLayer(Layer* t_layer)
    {
        m_layerInsert = m_layers.emplace(m_layerInsert, t_layer);
    }

    void LayerStack::pushOverlay(Layer *t_overlay)
    {
        m_layers.emplace_back(t_overlay);
    }

    void LayerStack::popLayer(Layer* t_layer)
    {
        auto it = std::find(m_layers.begin(), m_layerInsert, t_layer);
        if (it != m_layers.end())
        {
            m_layers.erase(it);
            m_layerInsert--;
        }
    }

    void LayerStack::popOverlay(Layer *t_overlay)
    {
        auto it = std::find(m_layerInsert, m_layers.end(), t_overlay);
        if (it != m_layers.end())
        {
            m_layers.erase(it);
        }
    }
}