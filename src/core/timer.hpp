#ifndef timer_hpp
#define timer_hpp

#include <iostream>
#include <chrono>

namespace mgl
{
    class Timer
    {
    public:
        
        Timer();
        
        void tick();
        
        void reset();
        inline double getDeltaTime() { return m_deltaTime.count(); }
        inline long int getElapsedTime() { return (long int)m_elepsedTime; }
        
        inline double getTimeScale() { return m_timeScale; }
        inline void timeScale(double t_t) { m_timeScale = t_t; }
        
    private:
    
        std::chrono::high_resolution_clock::time_point m_startTime;
        std::chrono::duration<double> m_deltaTime;

        double m_elepsedTime;
        double m_timeScale;
    };
}


#endif