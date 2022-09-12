#ifndef orthogrphicProjection_hpp
#define orthogrphicProjection_hpp

#include "projection.hpp"

namespace mgl
{
    class OrthogrphicProjection : public Projection
    {
    public:
    
        OrthogrphicProjection();
        virtual ~OrthogrphicProjection();

        virtual void onEvent(Event& e) override;
        bool onWindowResize(WindowResizeEvent& e);
    };
}

#endif