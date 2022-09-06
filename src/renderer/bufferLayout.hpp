#ifndef bufferLayout_hpp
#define bufferLayout_hpp

#include <mgl/mglpch.hpp>
#include "bufferVertex.hpp"

namespace mgl
{
    class BufferLayout
    {
    public:

        /// @brief push a vertex to the buffer layout
        /// @tparam _count the count of the data elements in the vertex
        /// @tparam _data_type the data type of the vertex
        /// @param t_normalized if the data type needs to be normalized (false by default)
        template<int _count, MglDataType _data_type>
        void push(bool t_normalized = false)
        {
            BufferVertex vertex = BufferVertex(_count, _data_type, t_normalized);
            m_vertices.push_back(vertex);
            m_strideBytes += vertex.getDataTypeSize() * _count;
        }

        /// @brief get the buffer layout as a vector of its buffer vertices
        /// @return list of buffer vertices
        inline std::vector<BufferVertex> getLayout() { return m_vertices; }
        /// @brief return the stride of the layout
        /// @return the total size in bytes of the buffer layout
        inline int getStride() { return m_strideBytes; }

    private:

        // * the vertices
        std::vector<BufferVertex> m_vertices;
        // * the stride of the vertex in bytes
        int m_strideBytes;
    };
}

#endif