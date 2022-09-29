#include "math.hpp"

namespace mgl
{
    float degToRad(float t_deg)
    {
        return ((t_deg*c_PI) / 180.0f);
    }
    
    float radToDeg(float t_rad)
    {
        return (c_PI / (180.0f*t_rad));
    }
    
    float map(float t_value, float t_min1, float t_max1, float t_min2, float t_max2) 
    {
        return t_min2 + (t_value - t_min1) * (t_max2 - t_min2) / (t_max1 - t_min1);
    }

    float map(float t_value, glm::vec2 t_origRng, glm::vec2 t_newRng)
    {
        float min1 = std::min(t_origRng.x, t_origRng.y);
        float min2 = std::min(t_newRng.x, t_newRng.y);
        float max1 = std::max(t_origRng.x, t_origRng.y);
        float max2 = std::max(t_newRng.x, t_newRng.y);
        return map(t_value, min1, max1, min2, max2);
    }

    float pythag1f(float t_a, float t_b)
    {
        return sqrt((t_a*t_a) + (t_b*t_b));
    }

    glm::vec2 pythag2f(glm::vec2 t_a, glm::vec2 t_b)
    {
        glm::vec2 result;
        for (int i = 0; i < 2; i++)
        {
            result[i] = pythag1f(t_a[i], t_b[i]);
        }

        return result;
    }

    glm::vec3 pythag3f(glm::vec3 t_a, glm::vec3 t_b)
    {
        glm::vec3 result;
        for (int i = 0; i < 3; i++)
        {
            result[i] = pythag1f(t_a[i], t_b[i]);
        }

        return result;
    }

    glm::vec4 pythag4f(glm::vec4 t_a, glm::vec4 t_b)
    {
        glm::vec4 result;
        for (int i = 0; i < 4; i++)
        {
            result[i] = pythag1f(t_a[i], t_b[i]);
        }

        return result;
    }

    bool equal(float t_a, float t_b)
    {
        return std::abs(t_a-t_b) <= c_EPSILON;
    }
}