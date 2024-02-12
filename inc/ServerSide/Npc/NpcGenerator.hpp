#pragma once

#include "NpcTypes.hpp"
#include "Npc.hpp"
#include "BasicNpc.hpp"

class NpcGenerator
{
public:
    NpcGenerator();
    ~NpcGenerator();
    Npc *generateNpc(int type);
    Npc *generateWhiteCat();
    Npc *generateCalicoCat();
    Npc *generateGhostCat();
    Npc *generateRadioactiveCat();
private:
};