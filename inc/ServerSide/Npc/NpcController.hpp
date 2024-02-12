#pragma once

#include <map>
#include "Scene.hpp"
#include "../../Data/vec2.hpp"
#include "BasicNpc.hpp"
#include "NpcGenerator.hpp"

class NpcController
{
public:
    static NpcController &getInstance();
    void update(float deltaTime);
    void handleNpcPositionReq(std::istringstream &iss);
    std::map<int, Npc *> npcs;
private:
    void _handleNewNpc(std::istringstream &iss, int id);
    void _handleNpcPosition(std::istringstream &iss, int id);

    NpcGenerator npcGenerator;
};
