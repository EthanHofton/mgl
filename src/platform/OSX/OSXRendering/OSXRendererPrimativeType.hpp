#ifndef OSXRendererPrimativeType_hpp
#define OSXRendererPrimativeType_hpp

#ifdef MGL_PLATFORM_OSX

#include <GL/glew.h>
#include <mgl/renderer/primativeType.hpp>

namespace mgl
{
    GLenum MGLPrimativeType2GL(MglPrimativeType t_primative);
    MglPrimativeType GLPrimativeType2MGL(GLenum t_primative);
}

#endif

#endif