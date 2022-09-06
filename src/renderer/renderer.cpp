#include "renderer.hpp"

namespace mgl
{
    Renderer::Renderer()
    {
        m_maxVerticeDataSizeBytes = Config::instance()->getGameConifg()["renderer_vertice_base_size_bytes"].GetInt();
        m_maxIndiceDataSizeBytes = Config::instance()->getGameConifg()["renderer_indice_base_size_bytes"].GetInt();

        m_verticeData = malloc(m_maxVerticeDataSizeBytes);
        m_indiceData = malloc(m_maxIndiceDataSizeBytes);

        m_verticeDataSizeBytes = m_maxIndiceDataSizeBytes;
        m_indiceDataSizeBytes = m_maxIndiceDataSizeBytes;

        m_bufferResized = false;
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
        while (m_verticeDataSizeBytes + t_verticeSizeBytes >= m_maxVerticeDataSizeBytes)
        {
            m_maxVerticeDataSizeBytes *= 2;
            m_verticeData = realloc(m_verticeData, m_maxVerticeDataSizeBytes);
            m_bufferResized = true;
        }

        // * test for overflow on indices
        while (m_verticeDataSizeBytes + t_indiceSizeBytes >= m_maxIndiceDataSizeBytes)
        {
            m_maxIndiceDataSizeBytes *= 2;
            m_indiceData = realloc(m_indiceData, m_maxIndiceDataSizeBytes);
            m_bufferResized = true;
        }

        // * copy vertice data into mem buf and increment the size pointers
        memcpy((void*)((char*)m_verticeData + m_verticeDataSizeBytes), t_vertices, t_verticeSizeBytes);
        memcpy((void*)((char*)m_indiceData + m_indiceDataSizeBytes), t_indices, t_indiceSizeBytes);

        m_verticeDataSizeBytes += t_verticeSizeBytes;
        m_indiceDataSizeBytes += t_indiceSizeBytes;
    }

    void Renderer::cleanBuffers()
    {
        // * reset buffer pointers
        m_verticeDataSizeBytes = 0;
        m_indiceDataSizeBytes = 0;
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