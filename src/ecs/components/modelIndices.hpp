#ifndef modelIndices_hpp
#define modelIndices_hpp

#include <mgl/mglpch.hpp>

namespace mgl
{
    struct ModelIndices
    {
        ModelIndices(std::vector<unsigned int> t_indices)
        {
            m_indices = t_indices;
        }

        std::vector<unsigned int> m_indices;
    };
}

#endif