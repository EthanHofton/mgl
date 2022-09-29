#ifndef color_hpp
#define color_hpp

#include <mgl/mglpch.hpp>

namespace mgl
{
    struct Color
    {
        Color(std::vector<glm::vec4> t_colors) : m_colors(t_colors) {}
        std::vector<glm::vec4> m_colors;

        int getSize() { return getStep() * m_colors.size(); }
        int getStep() { return sizeof(glm::vec4); }
        void getData(void *t_dest) { memcpy(t_dest, (void*)&m_colors[0], getSize()); }
    };
}

#endif