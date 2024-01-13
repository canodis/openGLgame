#pragma once

#include <chrono>

typedef std::chrono::time_point<std::chrono::high_resolution_clock> HighResClock;

class Timer 
{
public:
    Timer();
    void    start();
    double  elapsedSeconds();
    void    sleepMainThread();
    void    setMaxFPS(float maxFPS);

private:
    HighResClock    m_Start;
    HighResClock    m_End;
    float           m_MaxFPS;
};