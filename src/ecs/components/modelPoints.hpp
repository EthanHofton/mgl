#ifndef modelPoints_hpp
#define modelPoints_hpp

#include <mgl/mglpch.hpp>

namespace mgl
{
    class Renderer;
    struct ModelPoints
    {
        ModelPoints(std::vector<glm::vec3> t_vertices) : m_localVertices(t_vertices), m_worldVertices(t_vertices) {}

        void getData(void *t_dest) { memcpy(t_dest, (void*)m_worldVertices.data(), getSize()); }
        int getSize() { return getStep() * m_worldVertices.size(); }
        int getStep() { return sizeof(glm::vec3); }

        std::vector<glm::vec3> getLocalVertices() const { return m_localVertices; }
        std::vector<glm::vec3>& rgetLocalVertices() { m_updated = true; return m_localVertices; }
        void setLocalVertices(std::vector<glm::vec3> t_localVertices) { m_updated = true; m_localVertices = t_localVertices; }

    private:

        // * weather or not the **LOCAL** vertices have been updated or not (triggers world vert recal)
        bool m_updated = false;

        // * local store of the model points in model space
        std::vector<glm::vec3> m_localVertices;
        // * what actually gets drawn to the screen in world space
        std::vector<glm::vec3> m_worldVertices;

        friend class Renderer;
    };
}

#endif