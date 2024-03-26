#pragma once

#include "Stage.hpp"
#include "Game.hpp"

class LoginStage : public Stage
{
public:
    LoginStage();
    void initStage();
    void runStage();
    void endStage();
    ~LoginStage();

private:
    float windowWidth;
    float windowHeight;
    float windowPosX;
    float windowPosY;
};