#ifndef modelPoints_hpp
#define modelPoints_hpp

#include <mgl/mglpch.hpp>

namespace mgl
{
    struct ModelPoints
    {
        ModelPoints(std::vector<glm::vec3> t_vertices)
        {
            for (int i = 0; i < t_vertices.size(); i++)
            {
                m_localVertices.push_back(t_vertices[i]);
                m_worldVertices.push_back(t_vertices[i]);
            }
        }

        void getVertices(void *t_dest)
        {
            memcpy(t_dest, (void*)m_worldVertices.data(), getSize());
        }

        int getSize()
        {
            return getStep() * m_worldVertices.size();
        }

        int getStep()
        {
            return sizeof(glm::vec3);
        }

        std::vector<glm::vec3> m_localVertices;
        std::vector<glm::vec3> m_worldVertices;
    };
}

#endif