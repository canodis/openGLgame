#include "Navigator.hpp"
#include <glfw3.h>

Navigator::Navigator() : activeStage(nullptr), isRunning(true)
{
}

void Navigator::setActiveStage(Stage *stage)
{
    if (activeStage != nullptr)
    {
        activeStage->endStage();
        delete activeStage;
    }
    activeStage = stage;
    if (activeStage != nullptr)
        activeStage->initStage();
}

void Navigator::runActiveStage()
{
    if (activeStage != nullptr)
    {
        activeStage->runStage();
    }
    else
    {
        std::cout << "No active stage" << std::endl;
    }
}

Navigator &Navigator::getInstance()
{
    static Navigator instance;
    return instance;
}

void Navigator::exitGame()
{
    if (activeStage != nullptr)
    {
        activeStage->endStage();
        delete activeStage;
        activeStage = nullptr;
    }
    isRunning = false;
}