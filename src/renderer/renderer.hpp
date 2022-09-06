#ifndef renderer_hpp
#define renderer_hpp

#include <mgl/mglpch.hpp>
#include "bufferLayout.hpp"
#include "primativeType.hpp"

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


        // * to be implamented per platform
        static Renderer* create(const rendererProps& t_props);


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
    };
}

#endif