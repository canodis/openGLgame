#pragma once

class Stage
{
public:
    Stage();
    virtual void initStage() = 0;
    virtual void runStage() = 0;
    virtual void endStage() = 0;
    virtual ~Stage();
};