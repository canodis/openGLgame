#pragma once

class TurretNpc;
#include "Npc.hpp"
#include "ThrowObject.hpp"
#include <vector>

class TurretNpc : public Npc
{
public:
    TurretNpc();
    ~TurretNpc();
    void update(float deltaTime) override;
    void attack(glm::vec3 direction, int bulletId);
    void destroyBullet(int bulletId);
private:
    std::vector<ThrowObject *> throwObjects;
    ThrowObject *throwObjectPrefab;
    float radius;
    float attackSpeed;
    float cooldown;
};