#ifndef OSXRenderer_hpp
#define OSXRenderer_hpp

#ifdef MGL_PLATFORM_OSX

#include <mgl/renderer/renderer.hpp>
#include <GL/glew.h>
#include "OSXShader.hpp"

namespace mgl
{
    class OSXRenderer : public Renderer
    {
    public:

        OSXRenderer(const rendererProps&);
        virtual ~OSXRenderer();

        virtual void draw() override;

        // * uniform setting and getting
        virtual void addUniform(std::string t_uniformId) override;
        virtual void setUniform1i(std::string t_uniformId, int t_val) override;
        virtual void setUniform1f(std::string t_uniformId, float t_val) override;
        virtual void setUniform2i(std::string t_uniformId, glm::ivec2 t_val) override;
        virtual void setUniform2f(std::string t_uniformId, glm::vec2 t_val) override;
        virtual void setUniform3i(std::string t_uniformId, glm::ivec3 t_val) override;
        virtual void setUniform3f(std::string t_uniformId, glm::vec3 t_val) override;
        virtual void setUniform4i(std::string t_uniformId, glm::ivec4 t_val) override;
        virtual void setUniform4f(std::string t_uniformId, glm::vec4 t_val) override;
        virtual void setUnifromMatrix4fv(std::string t_uniformId, glm::mat4 t_val) override;

        static const std::string PROJECTION_UNIFORM_NAME;
        static const std::string VIEW_UNIFORM_NAME;

    private:

        void init();
        void release();

    private:

        unsigned int m_VAO;
        unsigned int m_VBO;
        unsigned int m_IBO;

        rendererProps m_options;
        OSXShader *m_shader;
    };
}

#endif

#endif