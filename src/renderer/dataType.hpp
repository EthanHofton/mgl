#ifndef dataType_hpp
#define dataType_hpp

namespace mgl
{
    enum MglDataType
    {
        MGL_BYTE,
        MGL_UNSIGNED_BYTE,
        MGL_SHORT,
        MGL_UNSIGNED_SHORT,
        MGL_INT,
        MGL_UNSIGNED_INT,
        MGL_HALF_FLOAT,
        MGL_FLOAT,
        MGL_DOUBLE,
        MGL_FIXED
    };

    unsigned int getMglDataTypeSize(MglDataType t_type);
}

#endif