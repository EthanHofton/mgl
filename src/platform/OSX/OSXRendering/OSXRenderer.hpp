#ifndef OSXRenderer_hpp
#define OSXRenderer_hpp

#ifdef MGL_PLATFORM_OSX

#include <mgl/renderer/renderer.hpp>
#include <GL/glew.h>
#include "OSXShader.hpp"

namespace mgl
{
    class OSXRenderer : public Renderer
    {
    public:

        OSXRenderer(const rendererProps&);
        virtual ~OSXRenderer();

        virtual void draw() override;

    private:

        void init();
        void release();

    private:

        unsigned int m_VAO;
        unsigned int m_VBO;
        unsigned int m_IBO;

        rendererProps m_options;
        OSXShader *m_shader;
    };
}

#endif

#endif