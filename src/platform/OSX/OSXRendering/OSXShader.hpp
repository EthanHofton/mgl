#ifndef OSXShader_hpp
#define OSXShader_hpp

#ifdef MGL_PLATFORM_OSX

#include <mgl/mglpch.hpp>
#include <mgl/util/util.hpp>
#include <GL/glew.h>

namespace mgl
{
    class OSXShader
    {
    public:

        OSXShader(std::string t_vert, std::string t_frag, std::string t_geom = "");
        ~OSXShader();

        inline unsigned int getShaderId() { return m_shaderId; }

        unsigned int getUniformLocation(std::string t_uniformId);
        void addUniform(std::string t_uniformId);

        void setUniform1i(std::string t_uniformId, int t_val);
        void setUniform1f(std::string t_uniformId, float t_val);
        void setUniform2i(std::string t_uniformId, glm::ivec2 t_val);
        void setUniform2f(std::string t_uniformId, glm::vec2 t_val);
        void setUniform3i(std::string t_uniformId, glm::ivec3 t_val);
        void setUniform3f(std::string t_uniformId, glm::vec3 t_val);
        void setUniform4i(std::string t_uniformId, glm::ivec4 t_val);
        void setUniform4f(std::string t_uniformId, glm::vec4 t_val);
        void setUniformMatrix4fv(std::string t_uniformId, glm::mat4 t_val);

        void useShader();

        inline bool hasVertexShader() { return !(m_vertexShaderFile == ""); }
        inline bool hasGeometryShader() { return !(m_geometryShaderFile == ""); }
        inline bool hasFragmentShader() { return !(m_fragmentShaderFile == ""); }

        inline std::string getVertexShader() { return m_vertexShaderCode; }
        inline std::string getVertexShaderFile() { return m_vertexShaderFile; }

        inline std::string getGeometryShader() { return m_geometryShaderCode; }
        inline std::string getGeometryShaderFile() { return m_geometryShaderFile; }

        inline std::string getFragmentShader() { return m_fragmentShaderCode; }
        inline std::string getFragmentShaderFile() { return m_fragmentShaderFile; }

    private:

        #define USE_SHADER_UNIFORM_MAP(uniform_map, gl_method, ...)\
            for (auto val : uniform_map)\
            {\
                unsigned int uniformLocation = getUniformLocation(val.first);\
                gl_method(uniformLocation, __VA_ARGS__);\
            }

        unsigned int m_shaderId;

        std::map<std::string, unsigned int> m_uniformMap;

        std::map<std::string, int>        m_uniform1iMap;
        std::map<std::string, float>      m_uniform1fMap;
        std::map<std::string, glm::ivec2> m_uniform2iMap;
        std::map<std::string, glm::vec2>  m_uniform2fMap;
        std::map<std::string, glm::ivec3> m_uniform3iMap;
        std::map<std::string, glm::vec3>  m_uniform3fMap;
        std::map<std::string, glm::ivec4> m_uniform4iMap;
        std::map<std::string, glm::vec4>  m_uniform4fMap;
        std::map<std::string, glm::mat4>  m_uniformMatrix4fvMap;

        void compileShader();
        void addShader(const char *t_shaderCode, GLenum t_shaderType);

        std::string m_vertexShaderFile;
        std::string m_geometryShaderFile;
        std::string m_fragmentShaderFile;

        std::string m_vertexShaderCode;
        std::string m_geometryShaderCode;
        std::string m_fragmentShaderCode;
    };
}

#endif

#endif