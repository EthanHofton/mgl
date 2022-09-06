#ifndef OSXErrorCheck_hpp
#define OSXErrorCheck_hpp

#ifdef MGL_PLATFORM_OSX

#include <GL/glew.h>

namespace mgl
{
    void checkOpenGLError();
}

#endif

#endif