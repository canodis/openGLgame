#pragma once

#include <map>
#include "Scene.hpp"
#include "../../Data/vec2.hpp"
#include "BasicNpc.hpp"
#include "NpcGenerator.hpp"
#include "ThrowObject.hpp"

class NpcController
{
public:
    static NpcController &getInstance();
    void update(float deltaTime);
    void handleNpcPositionReq(std::istringstream &iss);
    void handleNewTurret(std::istringstream &iss);
    void handleTurretAttack(std::istringstream &iss);
    void handleTurretBulletDestroy(std::istringstream &iss);
    void handleTurretHit(std::istringstream &iss);
    void handleNpcDie(std::istringstream &iss);

    void destroyNpc(int id);
    std::map<int, Npc *> npcs;

private:
    void _handleNewBasicNpc(std::istringstream &iss, int id);
    void _handleBasicNpcPosition(std::istringstream &iss, int id);
    NpcGenerator npcGenerator;
    std::map<int, ThrowObject> throwObjects;
};
