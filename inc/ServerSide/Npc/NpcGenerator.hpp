#pragma once

#include "NpcTypes.hpp"
#include "Npc.hpp"
#include "BasicNpc.hpp"
#include "TurretNpc.hpp"

class NpcGenerator
{
public:
    NpcGenerator();
    ~NpcGenerator();
    Npc *generateNpc(int type, float speed);
    Npc *generateWhiteCat(float speed);
    Npc *generateCalicoCat(float speed);
    Npc *generateGhostCat(float speed);
    Npc *generateRadioactiveCat(float speed);
    Npc *generateTurret();
private:
    Npc *generateBasicNpcTemplate(std::string texture);
};