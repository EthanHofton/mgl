#ifndef renderer_hpp
#define renderer_hpp

#include <mgl/mglpch.hpp>
#include "bufferLayout.hpp"
#include "primativeType.hpp"
#include <mgl/ecs/entity.hpp>
#include <mgl/ecs/components/modelIndices.hpp>
#include <mgl/ecs/components/modelPoints.hpp>
#include <mgl/ecs/components/transform.hpp>
#include <mgl/ecs/components/camera3D.hpp>
#include <mgl/ecs/components/camera2D.hpp>

namespace mgl
{
    // * props to be passed in when creating a new renderer
    struct rendererProps
    {
        // * empty for now 
        // * todo:
        //  * camera         (default: null)
        //  * projection     (default: null)
        //  * shader file    (required)
        //  * primative type (required)
        //  * buffer layout  (required)
        //  * wireframe      (default: false)
        //  * facecull       (default false)

        std::string m_vertexShaderPath;
        std::string m_fragmentShaderPath;
        std::string m_geometryShaderPath = "";
        MglPrimativeType m_primativeType;
        BufferLayout m_layout = BufferLayout();
        bool m_wireframeMode = false;
        bool m_cullFaceMode  = false;

        rendererProps(std::string t_vertexShaderPath, std::string t_fragmentShaderPath, MglPrimativeType t_primativeType) :
            m_vertexShaderPath(t_vertexShaderPath), m_fragmentShaderPath(t_fragmentShaderPath),
            m_primativeType(t_primativeType) {}
    };

    class Renderer
    {
    public:

        Renderer();
        virtual ~Renderer();

        // * draw function to be implamented per platform
        virtual void draw() = 0;


        // * push data methods
        void pushData(void* t_vertices, int t_verticeSizeBytes, void* t_indices, int t_indiceSizeBytes);

        // * push entity
        void pushEntity(Entity t_entity);

        // * push camera
        void pushCamera(Entity t_camera)
        {
            if (t_camera.hasComponent<Camera3D>())
            {
                m_camera = t_camera.getComponent<Camera3D>().getView();
            }
            
            if (t_camera.hasComponent<Camera2D>())
            {
                m_camera = t_camera.getComponent<Camera2D>().getView();
            }
        }

        // * to be implamented per platform
        static Renderer* create(const rendererProps& t_props);

        // * uniform setting and getting
        // * TO BE IMPLAMENTED PER PLATFORM
        virtual void addUniform(std::string t_uniformId) = 0;
        virtual void setUniform1i(std::string t_uniformId, int t_val) = 0;
        virtual void setUniform1f(std::string t_uniformId, float t_val) = 0;
        virtual void setUniform2i(std::string t_uniformId, glm::ivec2 t_val) = 0;
        virtual void setUniform2f(std::string t_uniformId, glm::vec2 t_val) = 0;
        virtual void setUniform3i(std::string t_uniformId, glm::ivec3 t_val) = 0;
        virtual void setUniform3f(std::string t_uniformId, glm::vec3 t_val) = 0;
        virtual void setUniform4i(std::string t_uniformId, glm::ivec4 t_val) = 0;
        virtual void setUniform4f(std::string t_uniformId, glm::vec4 t_val) = 0;
        virtual void setUnifromMatrix4fv(std::string t_uniformId, glm::mat4 t_val) = 0;

    protected:

        // * used to reset the buffer pointers
        void cleanBuffers();
        
        // * check if either buffer was resized
        bool bufferResized();

        void* m_verticeData;
        void* m_indiceData;
        int m_verticeDataPointer;
        int m_indiceDataPointer;

        int m_maxVerticeDataSizeBytes;
        int m_maxIndiceDataSizeBytes;

        int m_indiceOffset;

        bool m_bufferResized;

        glm::mat4 m_camera;

        // * TODO: Make transform only recaculate if the model or transform has been updated
        // entt::observer m_transformObserver();
    };
}

#endif