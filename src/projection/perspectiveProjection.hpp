#ifndef prespectiveProjection_hpp
#define prespectiveProjection_hpp

#include "projection.hpp"

namespace mgl
{
    class PerspectiveProjection : public Projection
    {
    public:
    
        PerspectiveProjection();
        virtual ~PerspectiveProjection();

        virtual void onEvent(Event& e) override;
        bool onWindowResize(WindowResizeEvent &e);
    };
}

#endif