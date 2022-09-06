#include "dataType.hpp"

namespace mgl
{
    unsigned int getMglDataTypeSize(MglDataType t_type)
    {
        switch (t_type)
        {
        case MGL_BYTE:
        case MGL_UNSIGNED_BYTE:
            return 1;
        case MGL_SHORT:
        case MGL_UNSIGNED_SHORT:
        case MGL_HALF_FLOAT:
            return 2;
        case MGL_INT:
        case MGL_UNSIGNED_INT:
        case MGL_FLOAT:
        case MGL_FIXED:
            return 4;
        case MGL_DOUBLE:
            return 8;
        }
    }
}