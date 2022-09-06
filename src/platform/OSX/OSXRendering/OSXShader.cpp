#include "OSXShader.hpp"

#ifdef MGL_PLATFORM_OSX

namespace mgl
{

    OSXShader::OSXShader(std::string t_vert, std::string t_frag, std::string t_geom)
    {
        m_vertexShaderFile = t_vert;
        m_vertexShaderCode = readFileWithNewline(m_vertexShaderFile);

        m_fragmentShaderFile = t_frag;
        m_fragmentShaderCode = readFileWithNewline(m_fragmentShaderFile);

        m_geometryShaderFile = t_geom;
        m_geometryShaderCode = (m_geometryShaderFile == "") ? "" : readFileWithNewline(m_geometryShaderFile);

        compileShader();
    }

    OSXShader::~OSXShader()
    {
        if (m_shaderId != 0)
        {
            glDeleteProgram(m_shaderId);
            m_shaderId = 0;
        }
    }

    void OSXShader::compileShader()
    {
        m_shaderId = glCreateProgram();

        if (!m_shaderId)
        {
            MGL_CORE_ERROR("Failed to create shader program");
            return;
        }

        addShader(m_vertexShaderCode.c_str(), GL_VERTEX_SHADER);
        
        if (hasGeometryShader())
        {
            addShader(m_geometryShaderCode.c_str(), GL_GEOMETRY_SHADER);
        }

        addShader(m_fragmentShaderCode.c_str(), GL_FRAGMENT_SHADER);

        int result = 0;
        char errorLog[1024] = { 0 };

        MGL_CORE_INFO("Aboute to link shader");

        glLinkProgram(m_shaderId);
        glGetProgramiv(m_shaderId, GL_LINK_STATUS, &result);
        if (!result)
        {
            glGetProgramInfoLog(m_shaderId, sizeof(errorLog), NULL, errorLog);
            MGL_CORE_ERROR("Error Linking Shader: {0}", errorLog);
            return;
        }

        MGL_CORE_INFO("Aboute to validate shader");

        glValidateProgram(m_shaderId);
        glGetProgramiv(m_shaderId, GL_VALIDATE_STATUS, &result);
        if (!result)
        {
            glGetProgramInfoLog(m_shaderId, sizeof(errorLog), NULL, errorLog);
            MGL_CORE_ERROR("Error Validating Shader: {0}", errorLog);
            return;
        }

        MGL_CORE_INFO("shader [id: {}, vertex: {}, geometry: {}, fragment: {}] compiled succsefully", m_shaderId, m_vertexShaderFile, m_geometryShaderFile, m_fragmentShaderFile);

        // * add uniforms
    }

    void OSXShader::addShader(const char *t_shaderCode, GLenum t_shaderType)
    {
        unsigned int shader = glCreateShader(t_shaderType);
        std::string shaderType = 
            (t_shaderType == GL_VERTEX_SHADER) ? "vertex shader" : 
            (t_shaderType == GL_GEOMETRY_SHADER) ? "geometry shader" :
            (t_shaderType == GL_FRAGMENT_SHADER) ? "fragment shader" : "(invalid shader type)";

        const char* code[1];
        code[0] = t_shaderCode;

        int codeLen[1];
        codeLen[0] = (int)std::strlen(t_shaderCode);

        glShaderSource(shader, 1, code, codeLen);
        glCompileShader(shader);

        int result = 0;
        char errorLog[1024] = { 0 };

        glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
        if (!result)
        {
            glGetShaderInfoLog(shader, sizeof(errorLog), NULL, errorLog);

            MGL_CORE_ERROR("Error compiling {}: {}", shaderType, errorLog);
        }

        MGL_CORE_INFO("Compiled {} succesfully", shaderType);

        glAttachShader(m_shaderId, shader);
    }

    void OSXShader::useShader()
    {
        glUseProgram(m_shaderId);

        USE_SHADER_UNIFORM_MAP(m_uniform1iMap, glUniform1i, val.second)
        USE_SHADER_UNIFORM_MAP(m_uniform1iMap, glUniform1f, val.second)

        USE_SHADER_UNIFORM_MAP(m_uniform2iMap, glUniform2i, val.second.x, val.second.y)
        USE_SHADER_UNIFORM_MAP(m_uniform2fMap, glUniform2f, val.second.x, val.second.y)

        USE_SHADER_UNIFORM_MAP(m_uniform3iMap, glUniform3i, val.second.x, val.second.y, val.second.z)
        USE_SHADER_UNIFORM_MAP(m_uniform3fMap, glUniform3f, val.second.x, val.second.y, val.second.z)

        USE_SHADER_UNIFORM_MAP(m_uniform4iMap, glUniform4i, val.second.x, val.second.y, val.second.z, val.second.w)
        USE_SHADER_UNIFORM_MAP(m_uniform4fMap, glUniform4f, val.second.x, val.second.y, val.second.z, val.second.w)
    }

    unsigned int OSXShader::getUniformLocation(std::string t_uniformId)
    {
        return m_uniformMap[t_uniformId];
    }

    void OSXShader::addUniform(std::string t_uniformId)
    {
        if (m_uniformMap.find(t_uniformId) == m_uniformMap.end())
        {
            m_uniformMap[t_uniformId] = glGetUniformLocation(m_shaderId, t_uniformId.c_str());
        }
    }

    void OSXShader::setUniform1i(std::string t_uniformId, int t_val)
    {
        m_uniform1iMap[t_uniformId] = t_val;
    }

    void OSXShader::setUniform1f(std::string t_uniformId, float t_val)
    {
        m_uniform1fMap[t_uniformId] = t_val;
    }

    void OSXShader::setUniform2i(std::string t_uniformId, glm::ivec2 t_val)
    {
        m_uniform2iMap[t_uniformId] = t_val;
    }

    void OSXShader::setUniform2f(std::string t_uniformId, glm::vec2 t_val)
    {
        m_uniform2fMap[t_uniformId] = t_val;
    }

    void OSXShader::setUniform3i(std::string t_uniformId, glm::ivec3 t_val)
    {
        m_uniform3iMap[t_uniformId] = t_val;
    }

    void OSXShader::setUniform3f(std::string t_uniformId, glm::vec3 t_val)
    {
        m_uniform3fMap[t_uniformId] = t_val;
    }

    void OSXShader::setUniform4i(std::string t_uniformId, glm::ivec4 t_val)
    {
        m_uniform4iMap[t_uniformId] = t_val;
    }

    void OSXShader::setUniform4f(std::string t_uniformId, glm::vec4 t_val)
    {
        m_uniform4fMap[t_uniformId] = t_val;
    }

}

#endif