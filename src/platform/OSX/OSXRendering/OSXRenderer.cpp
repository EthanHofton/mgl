#include <mgl/mglpch.hpp>
#include "OSXRenderer.hpp"
#include "OSXRendererDataType.hpp"
#include "OSXRendererPrimativeType.hpp"
#include "OSXErrorCheck.hpp"
#include <mgl/core/application.hpp>

#ifdef MGL_PLATFORM_OSX

namespace mgl
{
    const std::string OSXRenderer::PROJECTION_UNIFORM_NAME = "u_projection";
    const std::string OSXRenderer::VIEW_UNIFORM_NAME = "u_view";

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
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_maxIndiceDataSizeBytes, nullptr, GL_DYNAMIC_DRAW);

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
        m_shader->addUniform(PROJECTION_UNIFORM_NAME);
        m_shader->addUniform(VIEW_UNIFORM_NAME);
    }

    void OSXRenderer::draw()
    {
        // * do openGL draw

        // * check if the buffer was resized
        // * if resized, resize the array buffer
        // * if not, update the subdata of the array

        if (bufferResized())
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_maxIndiceDataSizeBytes, m_indiceData, GL_DYNAMIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            glBufferData(GL_ARRAY_BUFFER, m_maxVerticeDataSizeBytes, m_verticeData, GL_DYNAMIC_DRAW);
        }
        else
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_indiceDataPointer, m_indiceData);

            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, m_verticeDataPointer, m_verticeData);
        }

        m_shader->useShader();

        if (Application::getProjection() != nullptr)
        {
            m_shader->setUniformMatrix4fv(PROJECTION_UNIFORM_NAME, Application::getProjection()->getProjection());
        }

        m_shader->setUniformMatrix4fv(VIEW_UNIFORM_NAME, m_camera);

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

        std::vector<unsigned int> indicies((unsigned int*)(m_indiceData), (unsigned int*)((char *)m_indiceData + m_indiceDataPointer));
        std::vector<unsigned int> vertices((float*)(m_verticeData), (float*)((char *)m_verticeData + m_verticeDataPointer));

        // * draw elements
        glDrawElements(MGLPrimativeType2GL(m_options.m_primativeType), (int)m_indiceDataPointer / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

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

    void OSXRenderer::addUniform(std::string t_uniformId)
    {
        m_shader->addUniform(t_uniformId);
    }

    void OSXRenderer::setUniform1i(std::string t_uniformId, int t_val)
    {
        m_shader->setUniform1i(t_uniformId, t_val);
    }

    void OSXRenderer::setUniform1f(std::string t_uniformId, float t_val)
    {
        m_shader->setUniform1f(t_uniformId, t_val);
    }

    void OSXRenderer::setUniform2i(std::string t_uniformId, glm::ivec2 t_val)
    {
        m_shader->setUniform2i(t_uniformId, t_val);
    }

    void OSXRenderer::setUniform2f(std::string t_uniformId, glm::vec2 t_val)
    {
        m_shader->setUniform2f(t_uniformId, t_val);
    }

    void OSXRenderer::setUniform3i(std::string t_uniformId, glm::ivec3 t_val)
    {
        m_shader->setUniform3i(t_uniformId, t_val);
    }

    void OSXRenderer::setUniform3f(std::string t_uniformId, glm::vec3 t_val)
    {
        m_shader->setUniform3f(t_uniformId, t_val);
    }

    void OSXRenderer::setUniform4i(std::string t_uniformId, glm::ivec4 t_val)
    {
        m_shader->setUniform4i(t_uniformId, t_val);
    }

    void OSXRenderer::setUniform4f(std::string t_uniformId, glm::vec4 t_val)
    {
        m_shader->setUniform4f(t_uniformId, t_val);
    }

    void OSXRenderer::setUnifromMatrix4fv(std::string t_uniformId, glm::mat4 t_val)
    {
        m_shader->setUniformMatrix4fv(t_uniformId, t_val);
    }

}

#endif