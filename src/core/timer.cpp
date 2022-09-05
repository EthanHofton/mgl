#include <mgl/core/timer.hpp>

namespace mgl
{    
    Timer::Timer()
    {
        reset();
        m_timeScale = 1.0;
        m_deltaTime = std::chrono::duration<double>(0.0);
        m_elepsedTime = 0.0;
    }
    
    void Timer::tick()
    {
        m_deltaTime = std::chrono::high_resolution_clock::now() - m_startTime;
        m_elepsedTime += m_deltaTime.count();
    }
    
    void Timer::reset()
    {
        m_startTime = std::chrono::high_resolution_clock::now();
    }
}
