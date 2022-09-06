#include <mgl/mglpch.hpp>
#include "OSXRenderer.hpp"
#include "OSXRendererDataType.hpp"
#include "OSXRendererPrimativeType.hpp"

#ifdef MGL_PLATFORM_OSX

namespace mgl
{
    Renderer* Renderer::create(const rendererProps& t_props)
    {
        return new OSXRenderer(t_props);
    }

    OSXRenderer::OSXRenderer(const rendererProps& t_props) : m_options(t_props)
    {
        init();
    }

    OSXRenderer::~OSXRenderer()
    {
        release();
    }

    void OSXRenderer::init()
    {
        // * setup openGL buffers
        MGL_CORE_INFO("OSX RENDERER CREATED");

        // * create and bind vertex buffer
        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        glGenBuffers(1, &m_IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
        glBufferData(GL_ARRAY_BUFFER, m_maxIndiceDataSizeBytes, nullptr, GL_DYNAMIC_DRAW);

        glGenBuffers(1, &m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, m_maxVerticeDataSizeBytes, nullptr, GL_DYNAMIC_DRAW);

        // * initalize buffer layout
        int offset = 0;
        for (int i = 0; i < m_options.m_layout.getLayout().size(); i++)
        {
            BufferVertex vertex = m_options.m_layout.getLayout()[i];
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, vertex.getDataTypeSize(), MGLDataType2GL(vertex.getDataType()), vertex.isNormalaized(), m_options.m_layout.getStride(), (void*)(uintptr_t)(offset));
            offset += vertex.getVertexStride();
        }

        // * init shader
        m_shader = new OSXShader(m_options.m_vertexShaderPath, m_options.m_fragmentShaderPath, m_options.m_geometryShaderPath);
    }

    void OSXRenderer::draw()
    {
        // * do openGL draw

        // * check if the buffer was resized
        // * if resized, resize the array buffer
        // * if not, update the subdata of the array
        if (bufferResized())
        {
            glBufferData(GL_ARRAY_BUFFER, m_maxVerticeDataSizeBytes, m_verticeData, GL_DYNAMIC_DRAW);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_maxIndiceDataSizeBytes, m_indiceData, GL_DYNAMIC_DRAW);
        }
        else
        {
            glBufferSubData(GL_ARRAY_BUFFER, 0, m_verticeDataSizeBytes, m_verticeData);
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_indiceDataSizeBytes, m_indiceData);
        }

        m_shader->useShader();
        // * TODO: bind textures here
        // * TODO: bind UBOs here

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

        // * check if wireframe enabled
        if (m_options.m_wireframeMode)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }

        // * check if face culling is enabled
        if (m_options.m_cullFaceMode)
        {
            glEnable(GL_CULL_FACE);
        }

        // * draw elements
        glDrawElements(MGLPrimativeType2GL(m_options.m_primativeType), (int)m_indiceDataSizeBytes / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

        // * disabled wireframe if enabled
        if (m_options.m_wireframeMode)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        // * disabled face culling if enabled
        if (m_options.m_cullFaceMode)
        {
            glDisable(GL_CULL_FACE);
        }

        // * clean the buffers for the next render pass
        cleanBuffers();
    }

    void OSXRenderer::release()
    {
        // * clean up openGL buffers
        MGL_CORE_INFO("OSX RENDERER DELETED");

        // * cleanup buffers
        if (m_VAO != 0)
        {
            glDeleteBuffers(1, &m_VAO);
        }

        if (m_IBO != 0)
        {
            glDeleteBuffers(1, &m_IBO);
        }

        if (m_VBO != 0)
        {
            glDeleteBuffers(1, &m_VBO);
        }

        // * delete shader
        delete m_shader;
    }
}

#endif