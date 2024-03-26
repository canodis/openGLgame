#pragma once

#include "Navigator.hpp"
#include <glad.h>
#include <glfw3.h>

class BlackStage : public Stage
{
public:
    BlackStage();
    void initStage() override;
    void runStage() override;
    void endStage() override;
    ~BlackStage();
private:
    GLFWwindow *window;
};