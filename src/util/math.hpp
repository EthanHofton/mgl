#ifndef math_hpp
#define math_hpp

#include <mgl/mglpch.hpp>

namespace mgl
{
    const float c_PI = 3.14159265359f;
    const float c_HALF_PI = 1.57079632679f;
    const float c_TAU = 6.28318530718f;
    const float c_E = 2.71828182846f;
    const float c_EPSILON = 0.0001f;
    const glm::vec3 c_G = {0.0f, -9.81f, 0.0f};

    // * comparison with c_EPSILON tolarance
    bool equal(float t_a, float t_b);

    float pythag1f(float t_a, float t_b);
    glm::vec2 pythag2f(glm::vec2 t_a, glm::vec2 t_b);
    glm::vec3 pythag3f(glm::vec3 t_a, glm::vec3 t_b);
    glm::vec4 pythag4f(glm::vec4 t_a, glm::vec4 t_b);

    float degToRad(float t_deg);
    float radToDeg(float t_rad);

    float map(float t_value, float t_min1, float t_max1, float t_min2, float t_max2);
    float map(float t_value, glm::vec2 t_origRng, glm::vec2 t_newRng);
}

#endif