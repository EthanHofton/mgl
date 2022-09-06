#ifndef primativeType_hpp
#define primativeType_hpp

namespace mgl
{
    enum MglPrimativeType
    {
        MGL_POINTS,

        MGL_LINES,
        MGL_LINE_LOOP,
        MGL_LINE_STRIP,

        MGL_TRIANGLES,
        MGL_TRIANGLE_STRIP,
        MGL_TRIANGLE_FAN,

        MGL_LINES_ADJACENCY,
        MGL_LINE_STRIP_ADJACENCY,
        MGL_TRIANGLES_ADJACENCY,
        MGL_TRIANGLE_STRIP_ADJACENCY
    };
}

#endif