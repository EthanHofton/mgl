#ifndef projection_hpp
#define projection_hpp

#include <mgl/mglpch.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <mgl/events/event.hpp>
#include <mgl/events/applicationEvent.hpp>

namespace mgl
{
    class Projection
    {
    public:

        Projection() {}
        virtual ~Projection() {}

        virtual void onEvent(Event& e) = 0;

        inline glm::mat4& getProjection() { return m_projection; }

    protected:

        glm::mat4 m_projection;
    };
}

#endif