#include "TurretNpc.hpp"
#include "Scene.hpp"

TurretNpc::TurretNpc()
{
    attackSpeed = 2.5f;
    radius = 5.0f;
    cooldown = attackSpeed;
    throwObjectPrefab = new ThrowObject();
    throwObjectPrefab->obj = Scene::getInstance().gameObjectManager->CreateRectangle();
    throwObjectPrefab->obj->SetTexture(Scene::getInstance().textureManager->loadTexture("textures/bullet.png"));
}

void TurretNpc::update(float deltaTime)
{
    obj->update(deltaTime);
    for (auto &bullet : throwObjects)
    {
        bullet->update(deltaTime);
    }
}

void TurretNpc::attack(glm::vec3 direction, int bulletId)
{
    float angle = atan2(direction.y, direction.x) * 57.2958f;
    obj->transform.rotation = glm::vec3(0, 0, angle);
    ThrowObject *throwObject = new ThrowObject(bulletId, direction, *throwObjectPrefab->obj);
    throwObjects.push_back(throwObject);
}

void TurretNpc::destroyBullet(int bulletId)
{
    throwObjects.erase(std::remove_if(throwObjects.begin(), throwObjects.end(),
                                      [bulletId](auto &throwObject)
                                      { return throwObject->id == bulletId; }),
                       throwObjects.end());
}

TurretNpc::~TurretNpc() {}