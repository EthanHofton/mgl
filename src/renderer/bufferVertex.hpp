#ifndef bufferVertex_hpp
#define bufferVertex_hpp

#include "dataType.hpp"

namespace mgl
{
    class BufferLayout;
    class BufferVertex
    {
    friend BufferLayout;
    private:
        /// @brief constructor for BufferVertex
        /// @param t_count the number of elements vertex contains
        /// @param t_dataType the data type of the vertex
        /// @param t_dataTypeSizeBytes size of each element
        /// @param t_normalized if the elements need normalizing
        /// @param t_offsetBytes offset of the vertex in the layout
        BufferVertex(int t_count, MglDataType t_dataType, bool t_normalized) : 
            m_count(t_count), m_dataType(t_dataType), m_normalized(t_normalized) {}

    public:

        /// @brief get the count of data elements in the vertex
        /// @return number of data elements in the vertex
        inline int getCount() { return m_count; }
        /// @brief get the size of the data type
        /// @return size of the data type in bytes
        inline unsigned int getDataTypeSize() { return getMglDataTypeSize(m_dataType); }
        /// @brief get if the data elements need to be normaized or not
        /// @return if the elements need normalizing
        inline bool isNormalaized() { return m_normalized; }
        /// @brief get the data type of the vertex
        /// @return vertex data type
        inline MglDataType getDataType() { return m_dataType; }
        /// @brief gets the vertex stride
        /// @return the number of bytes the vertex takes up
        inline int getVertexStride() { return getDataTypeSize() * m_count; }

    private:

        // * count of elements in the vertex
        int m_count;
        // * store the data type
        MglDataType m_dataType;
        // * if the elements need normalizing
        bool m_normalized;
    };
}

#endif