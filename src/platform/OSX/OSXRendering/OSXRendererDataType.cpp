#include "OSXRendererDataType.hpp"

#ifdef MGL_PLATFORM_OSX

namespace mgl
{
    GLenum MGLDataType2GL(MglDataType t_dataType)
    {
        switch (t_dataType)
        {
            case MGL_BYTE:
                return GL_BYTE;
            case MGL_UNSIGNED_BYTE:
                return GL_UNSIGNED_BYTE;
            case MGL_SHORT:
                return GL_SHORT;
            case MGL_UNSIGNED_SHORT:
                return GL_UNSIGNED_SHORT;
            case MGL_INT:
                return GL_INT;
            case MGL_UNSIGNED_INT:
                return GL_UNSIGNED_INT;
            case MGL_HALF_FLOAT:
                return GL_HALF_FLOAT;
            case MGL_FLOAT:
                return GL_FLOAT;
            case MGL_DOUBLE:
                return GL_DOUBLE;
            case MGL_FIXED:
                return GL_FIXED;
        }
    }

    MglDataType GLDataType2MGL(GLenum t_dataType)
    {
        switch (t_dataType)
        {
            case GL_BYTE:
                return MGL_BYTE;
            case GL_UNSIGNED_BYTE:
                return MGL_UNSIGNED_BYTE;
            case GL_SHORT:
                return MGL_SHORT;
            case GL_UNSIGNED_SHORT:
                return MGL_UNSIGNED_SHORT;
            case GL_INT:
                return MGL_INT;
            case GL_UNSIGNED_INT:
                return MGL_UNSIGNED_INT;
            case GL_HALF_FLOAT:
                return MGL_HALF_FLOAT;
            case GL_FLOAT:
                return MGL_FLOAT;
            case GL_DOUBLE:
                return MGL_DOUBLE;
            case GL_FIXED:
                return MGL_FIXED;
            default:
                return MGL_FLOAT;
        }
    }
}

#endif