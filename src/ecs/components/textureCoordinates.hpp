#ifndef textureCoordinates_hpp
#define textureCoordinates_hpp

#include <mgl/mglpch.hpp>

namespace mgl
{
    class TextureCoordinates
    {
        TextureCoordinates(std::vector<glm::vec2> t_coords) : m_textureCoords(t_coords) {}
        std::vector<glm::vec2> m_textureCoords;

        int getStride() { return sizeof(glm::vec2); }
        int getSize() { return getStride() * m_textureCoords.size(); }
        void getData(void* t_dest) { memcpy(t_dest, (void*)&m_textureCoords[0], getSize()); }
    };
}

#endif