#ifndef util_color_hpp
#define util_color_hpp

#include <mgl/mglpch.hpp>

namespace mgl
{
    glm::vec3 hex2rgb(std::string t_hex);
    glm::vec4 hex2rgba(std::string t_hex);
    glm::vec4 hex2rgba(std::string t_hex, float t_alpha);
    std::string rgb2hex(glm::vec3 rgb);
    std::string rgb2hex(glm::vec4 rgba);
}

#endif