#pragma once

#include "Npc.hpp"

class BasicNpc : public Npc
{
public:
    BasicNpc();
    ~BasicNpc();
    void update(float deltaTime) override;
private:

};