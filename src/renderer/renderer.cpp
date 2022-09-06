#include "renderer.hpp"

namespace mgl
{
    Renderer::Renderer()
    {
        m_maxVerticeDataSizeBytes = Config::instance()->getGameConifg()["renderer_vertice_base_size_bytes"].GetInt();
        m_maxIndiceDataSizeBytes = Config::instance()->getGameConifg()["renderer_indice_base_size_bytes"].GetInt();

        m_verticeData = malloc(m_maxVerticeDataSizeBytes);
        m_indiceData = malloc(m_maxIndiceDataSizeBytes);

        m_verticeDataPointer = 0;
        m_indiceDataPointer = 0;

        m_bufferResized = false;
        m_indiceOffset = 0;
    }

    Renderer::~Renderer()
    {
        // delete the vertice data
        if (m_verticeData != nullptr)
        {
            free(m_verticeData);
            m_verticeData = nullptr;
        }

        // delete the indice data
        if (m_indiceData != nullptr)
        {
            free(m_indiceData);
            m_indiceData = nullptr;
        }
    }

    void Renderer::pushData(void* t_vertices, int t_verticeSizeBytes, void* t_indices, int t_indiceSizeBytes)
    {
        // * test for overflow on vertices
        while (m_verticeDataPointer + t_verticeSizeBytes >= m_maxVerticeDataSizeBytes)
        {
            m_maxVerticeDataSizeBytes *= 2;
            m_verticeData = realloc(m_verticeData, m_maxVerticeDataSizeBytes);
            m_bufferResized = true;
        }

        // * test for overflow on indices
        while (m_indiceDataPointer + t_indiceSizeBytes >= m_maxIndiceDataSizeBytes)
        {
            m_maxIndiceDataSizeBytes *= 2;
            m_indiceData = realloc(m_indiceData, m_maxIndiceDataSizeBytes);
            m_bufferResized = true;
        }

        // * find the max value of the indice data
        unsigned int* indicesCopy = (unsigned int*)malloc(t_indiceSizeBytes);
        memcpy(indicesCopy, t_indices, t_indiceSizeBytes);
        int maxVal = *std::max_element(indicesCopy, (unsigned int*)((char*)indicesCopy + t_indiceSizeBytes));

        // * increment the indices by the max values
        for (int i = 0; i < t_indiceSizeBytes / sizeof(unsigned int); i++)
            indicesCopy[i] += m_indiceOffset;
        m_indiceOffset += maxVal + 1;

        // * copy vertice data into mem buf and increment the size pointers
        memcpy((void*)((char*)m_verticeData + m_verticeDataPointer), t_vertices, t_verticeSizeBytes);
        memcpy((void*)((char*)m_indiceData + m_indiceDataPointer), indicesCopy, t_indiceSizeBytes);

        m_verticeDataPointer += t_verticeSizeBytes;
        m_indiceDataPointer += t_indiceSizeBytes;
    }

    void Renderer::cleanBuffers()
    {
        // * reset buffer pointers
        m_verticeDataPointer = 0;
        m_indiceDataPointer = 0;

        // * reset indice offset
        m_indiceOffset = 0;
    }

    bool Renderer::bufferResized()
    {
        if (m_bufferResized)
        {
            m_bufferResized = false;
            return true;
        }

        return false;
    }
}