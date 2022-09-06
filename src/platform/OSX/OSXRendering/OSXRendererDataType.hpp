#ifndef OSXBufferVertexDataType_hpp
#define OSXBufferVertexDataType_hpp

#ifdef MGL_PLATFORM_OSX

#include <GL/glew.h>
#include <mgl/renderer/dataType.hpp>

namespace mgl
{
    GLenum MGLDataType2GL(MglDataType t_dataType);
    MglDataType GLDataType2MGL(GLenum t_dataType);
}

#endif

#endif