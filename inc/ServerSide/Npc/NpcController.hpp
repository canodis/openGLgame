#pragma once

#include <map>
#include "Scene.hpp"
#include "../../Data/vec2.hpp"
#include "BasicNpc.hpp"
#include "NpcGenerator.hpp"
#include "ThrowObject.hpp"
#include "BasicNpcPositionPackage.hpp"
#include "NewBasicNpcPackage.hpp"

class NpcController
{
public:
    static NpcController &getInstance();
    void update(float deltaTime);
    void handleNewTurret(std::istringstream &iss);
    void handleTurretAttack(std::istringstream &iss);
    void handleTurretBulletDestroy(std::istringstream &iss);
    void handleTurretHit(std::istringstream &iss);
    void handleNpcDie(std::istringstream &iss);

    void handleNewBasicNpc(NewBasicNpcPackage &package);
    void handleBasicNpcPosition(BasicNpcPositionPackage &package);

    void destroyNpc(int id);
    std::map<int, Npc *> npcs;
private:
    NpcGenerator npcGenerator;
    std::map<int, ThrowObject> throwObjects;
};
