#include "NpcController.hpp"
#include "Client.hpp"
#include <sstream>

void NpcController::handleNewBasicNpc(NewBasicNpcPackage &package)
{
    std::lock_guard<std::mutex> lock(Client::getInstance()._npcMutex);

    npcs[package.id] = npcGenerator.generateNpc(package.id, package.speed);
    Npc *npc = npcs[package.id];
    
    npc->setSpeed(package.speed);
    npc->setHealth(package.health);

    npc->obj->transform.position.x = package.x;
    npc->obj->transform.position.y = package.y;

    npc->targetPosition.x = package.targetX;
    npc->targetPosition.y = package.targetY;
}

void NpcController::handleBasicNpcPosition(BasicNpcPositionPackage &package)
{
    std::lock_guard<std::mutex> lock(Client::getInstance()._npcMutex);
    
    Npc *npc = npcs[package.id];
    npc->obj->transform.position.x = package.x;
    npc->obj->transform.position.y = package.y;
    npc->targetPosition.x = package.targetX;
    npc->targetPosition.y = package.targetY;
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
    float x, y, speed;
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
    float x, y, speed;
    float directionX, directionY;
    iss >> turretId >> bulletId >> speed >> x >> y >> directionX >> directionY;
    if (npcs.find(turretId) != npcs.end())
    {
        TurretNpc *turret = dynamic_cast<TurretNpc *>(npcs[turretId]);
        if (turret)
        {
            turret->attack({directionX, directionY, 0}, bulletId , speed);
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
    std::lock_guard<std::mutex> lock(Client::getInstance()._npcMutex);
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