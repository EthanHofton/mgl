#include "OSXRendererPrimativeType.hpp"

#ifdef MGL_PLATFORM_OSX

namespace mgl
{
    GLenum MGLPrimativeType2GL(MglPrimativeType t_primative)
    {
        switch (t_primative)
        {
            case MGL_POINTS:
                return GL_POINTS;
            case MGL_LINES:
                return GL_LINES;
            case MGL_LINE_LOOP:
                return GL_LINE_LOOP;
            case MGL_LINE_STRIP:
                return GL_LINE_STRIP;
            case MGL_TRIANGLES:
                return GL_TRIANGLES;
            case MGL_TRIANGLE_STRIP:
                return GL_TRIANGLE_STRIP;
            case MGL_TRIANGLE_FAN:
                return GL_TRIANGLE_FAN;
            case MGL_LINES_ADJACENCY:
                return GL_LINES_ADJACENCY;
            case MGL_LINE_STRIP_ADJACENCY:
                return GL_LINE_STRIP_ADJACENCY;
            case MGL_TRIANGLES_ADJACENCY:
                return GL_TRIANGLES_ADJACENCY;
            case MGL_TRIANGLE_STRIP_ADJACENCY:
                return GL_TRIANGLE_STRIP_ADJACENCY;
        }
    }

    MglPrimativeType GLPrimativeType2MGL(GLenum t_primative)
    {
        switch (t_primative)
        {
            case GL_POINTS:
                return MGL_POINTS;
            case GL_LINES:
                return MGL_LINES;
            case GL_LINE_LOOP:
                return MGL_LINE_LOOP;
            case GL_LINE_STRIP:
                return MGL_LINE_STRIP;
            case GL_TRIANGLES:
                return MGL_TRIANGLES;
            case GL_TRIANGLE_STRIP:
                return MGL_TRIANGLE_STRIP;
            case GL_TRIANGLE_FAN:
                return MGL_TRIANGLE_FAN;
            case GL_LINES_ADJACENCY:
                return MGL_LINES_ADJACENCY;
            case GL_LINE_STRIP_ADJACENCY:
                return MGL_LINE_STRIP_ADJACENCY;
            case GL_TRIANGLES_ADJACENCY:
                return MGL_TRIANGLES_ADJACENCY;
            case GL_TRIANGLE_STRIP_ADJACENCY:
                return MGL_TRIANGLE_STRIP_ADJACENCY;
            default:
                return MGL_TRIANGLES;
        }
    }
}

#endif