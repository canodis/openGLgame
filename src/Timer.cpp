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

    // Maksimum FPS'i saniyede süre olarak hesapla (örneğin 60 FPS için 1/60 = 0.01667 saniye)
    double maxFrameTime = 1.0 / m_MaxFPS;

    // Eğer çerçeve süresi, izin verilen maksimum süreden daha kısa ise, fark kadar beklet
    if (elapsedSeconds < maxFrameTime) {
        double timeToWait = maxFrameTime - elapsedSeconds;
        std::this_thread::sleep_for(std::chrono::duration<double>(timeToWait));

        // Uykudan sonra zamanı güncelle
        m_End = std::chrono::high_resolution_clock::now();
        diff = m_End - m_Start;
    }

    m_Start = m_End;

    // Geçen toplam süreyi döndür
    return diff.count();
}