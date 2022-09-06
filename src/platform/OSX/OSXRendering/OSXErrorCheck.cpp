#include "OSXErrorCheck.hpp"
#include <mgl/mglpch.hpp>

#ifdef MGL_PLATFORM_OSX

namespace mgl
{
    void checkOpenGLError()
    {
        GLenum err;
        while((err = glGetError()) != GL_NO_ERROR)
        {
            MGL_CORE_ERROR("OpenGL Error: 0x{:x}", err);
        }
    }
}

#endif