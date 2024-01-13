#include "Timer.hpp"
#include <thread>

Timer::Timer()
{
    m_MaxFPS = 60;
}

void    Timer::start()
{
    m_Start = std::chrono::high_resolution_clock::now();
}

double Timer::elapsedSeconds() {
    m_End = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> diff = m_End - m_Start;
    double elapsedSeconds = diff.count();
    double maxFrameTime = 1.0 / m_MaxFPS;

    if (elapsedSeconds < maxFrameTime) {
        double timeToWait = maxFrameTime - elapsedSeconds;
        std::this_thread::sleep_for(std::chrono::duration<double>(timeToWait));

        m_End = std::chrono::high_resolution_clock::now();
        diff = m_End - m_Start;
    }
    m_Start = m_End;
    return diff.count();
}

void    Timer::setMaxFPS(float maxFPS)
{
    m_MaxFPS = maxFPS;
}