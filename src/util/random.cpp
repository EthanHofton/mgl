#include "random.hpp"

namespace mgl
{
    prng uuidGen::s_rngGen;

    prng::prng(std::string t_seed)
    {
        std::random_device rd;
        m_generator = std::mt19937(rd());

        m_seed = (t_seed == "") ? std::to_string(getpid() * time(NULL)) : t_seed;

        std::seed_seq seed(m_seed.begin(), m_seed.end());

        m_generator.seed(seed);
    }

    float prng::randf(float t_lower, float t_upper)
    {
        std::uniform_real_distribution<> dist(t_lower, t_upper);
        return dist(m_generator);
    }

    int prng::randi(int t_lower, int t_upper)
    {
        std::uniform_int_distribution<> dist(t_lower, t_upper);
        return dist(m_generator);
    }

    std::string uuidGen::get(int t_len)
    {
        std::stringstream ss;
        int i;
        ss << std::hex;
        for (i = 0; i < 8; i++) {
            ss << s_rngGen.randi(0, 15);
        }
        
        ss << "-";
        for (i = 0; i < 4; i++) {
            ss << s_rngGen.randi(0, 15);
        }

        ss << "-4";
        for (i = 0; i < 3; i++) {
            ss << s_rngGen.randi(0, 15);
        }

        ss << "-";
        ss << s_rngGen.randi(8, 11);
        for (i = 0; i < 3; i++) {
            ss << s_rngGen.randi(0, 15);
        }

        ss << "-";
        for (i = 0; i < 12; i++) {
            ss << s_rngGen.randi(0, 15);
        }

        return ss.str();
    }
}