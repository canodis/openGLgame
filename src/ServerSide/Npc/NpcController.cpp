#include "NpcController.hpp"
#include <sstream>
#include "Client.hpp"

void NpcController::_handleNewNpc(std::istringstream &iss, int id)
{
    int npcType;
    float x, y;
    float targetX, targetY;
    float speed, health;
    iss >> x >> y >> targetX >> targetY >> speed >> health >> npcType;
    npcs[id] = npcGenerator.generateNpc(npcType, speed);
    Npc *npc = npcs[id];
    
    npc->setSpeed(speed);
    npc->setHealth(health);

    npc->obj->transform.position.x = x;
    npc->obj->transform.position.y = y;

    npc->targetPosition.x = targetX;
    npc->targetPosition.y = targetY;
}

void NpcController::handleNpcPositionReq(std::istringstream &iss)
{
    int id;
    iss >> id;
    std::lock_guard<std::mutex> lock(Client::getInstance()._npcMutex);
    if (npcs.find(id) != npcs.end())
    {
        _handleNpcPosition(iss, id);
    }
    else
    {
        _handleNewNpc(iss, id);
    }
}

void NpcController::_handleNpcPosition(std::istringstream &iss, int id)
{
    float x, y;
    float targetX, targetY;
    iss >> x >> y >> targetX >> targetY;
    npcs[id]->targetPosition.x = x;
    npcs[id]->targetPosition.y = y;
}

void NpcController::update(float deltaTime)
{
    for (auto &npc : npcs)
    {
        npc.second->update(deltaTime);
        npc.second->obj->update(deltaTime);
    }
}

NpcController &NpcController::getInstance()
{
    static NpcController instance;
    return instance;
}