#include "NpcController.hpp"
#include <sstream>
#include "Client.hpp"

void NpcController::_handleNewBasicNpc(std::istringstream &iss, int id)
{
    int npcType;
    float x, y;
    float targetX, targetY;
    float speed, health;
    iss >> x >> y >> targetX >> targetY >> speed >> health >> npcType;
    npcs[id] = npcGenerator.generateNpc(npcType, speed);
    Npc *npc = npcs[id];
    
    npc->setSpeed(speed);
    npc->setHealth(10);

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
        _handleBasicNpcPosition(iss, id);
    }
    else
    {
        _handleNewBasicNpc(iss, id);
    }
}

void NpcController::_handleBasicNpcPosition(std::istringstream &iss, int id)
{
    float x, y;
    float targetX, targetY;
    iss >> x >> y >> targetX >> targetY;
    npcs[id]->targetPosition.x = targetX;
    npcs[id]->targetPosition.y = targetY;
}

void NpcController::update(float deltaTime)
{
    for (auto &npc : npcs)
    {
        npc.second->update(deltaTime);
    }
}

NpcController &NpcController::getInstance()
{
    static NpcController instance;
    return instance;
}

void NpcController::handleNewTurret(std::istringstream &iss)
{
    int id;
    float x, y;
    iss >> id >> x >> y;
    if (npcs.find(id) != npcs.end())
    {
        npcs[id]->obj->transform.position.x = x;
        npcs[id]->obj->transform.position.y = y;
    }
    else
    {
        npcs[id] = npcGenerator.generateNpc(NpcType::Turret, -1);
        npcs[id]->obj->transform.position.x = x;
        npcs[id]->obj->transform.position.y = y;
    }
}

void NpcController::handleTurretAttack(std::istringstream &iss)
{
    int turretId, bulletId;
    float x, y;
    float directionX, directionY;
    iss >> turretId >> bulletId >> x >> y >> directionX >> directionY;
    if (npcs.find(turretId) != npcs.end())
    {
        TurretNpc *turret = dynamic_cast<TurretNpc *>(npcs[turretId]);
        if (turret)
        {
            turret->attack({directionX, directionY, 0}, bulletId);
        }
    }
}

void NpcController::handleTurretBulletDestroy(std::istringstream &iss)
{
    int turretId, bulletId;
    iss >> turretId >> bulletId;
    if (npcs.find(turretId) != npcs.end())
    {
        TurretNpc *turret = dynamic_cast<TurretNpc *>(npcs[turretId]);
        if (turret)
        {
            turret->destroyBullet(bulletId);
        }
    }
}

void NpcController::handleTurretHit(std::istringstream &iss)
{
    int turretId, bulletId, npcId;
    iss >> turretId >> bulletId >> npcId;
    if (npcs.find(turretId) != npcs.end())
    {
        TurretNpc *turret = dynamic_cast<TurretNpc *>(npcs[turretId]);
        if (turret)
        {
            turret->destroyBullet(bulletId);
        }
    }
}

void NpcController::destroyNpc(int id)
{
    if (npcs.find(id) != npcs.end())
    {
        delete npcs[id];
        npcs.erase(id); 
    }
}

void NpcController::handleNpcDie(std::istringstream &iss)
{
    int id;
    iss >> id;
    destroyNpc(id);
}