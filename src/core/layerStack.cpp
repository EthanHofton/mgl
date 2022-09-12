#include "layerStack.hpp"

namespace mgl
{
    LayerStack::~LayerStack()
    {
        for (Layer* layer : m_layers)
        {
            layer->onDetach();
            delete layer;
        }
    }

    void LayerStack::pushLayer(Layer* t_layer)
    {
        t_layer->onAttach();
        m_layers.emplace(m_layers.begin() + m_layerInsertIndex, t_layer);
        m_layerInsertIndex++;
    }

    void LayerStack::pushOverlay(Layer *t_overlay)
    {
        t_overlay->onAttach();
        m_layers.emplace_back(t_overlay);
    }

    void LayerStack::popLayer(Layer* t_layer)
    {
        auto it = std::find(m_layers.begin(), m_layers.begin() + m_layerInsertIndex, t_layer);
        if (it != m_layers.begin() + m_layerInsertIndex)
        {
            t_layer->onDetach();
            m_layers.erase(it);
            m_layerInsertIndex--;
        }
    }

    void LayerStack::popOverlay(Layer *t_overlay)
    {
        auto it = std::find(m_layers.begin() + m_layerInsertIndex, m_layers.end(), t_overlay);
        if (it != m_layers.end())
        {
            t_overlay->onDetach();
            m_layers.erase(it);
        }
    }
}