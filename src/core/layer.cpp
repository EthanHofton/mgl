#include "layer.hpp"
#include <mgl/mglpch.hpp>

namespace mgl
{
    Layer::Layer(const std::string& t_debugName ) : m_debugName(t_debugName) {}
    Layer::~Layer() {}
}