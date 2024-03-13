#pragma once

#include <functional>
#include "Stage.hpp"
#include <iostream>

class Navigator
{
public:
    static Navigator &getInstance();
    void setActiveStage(Stage *stage);
    void runActiveStage();
    void exitGame();
    bool isRunning;
private:
    Navigator();
    Stage *activeStage;
};
