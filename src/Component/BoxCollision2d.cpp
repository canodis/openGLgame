#include "BoxCollision2d.hpp"
#include "Scene.hpp"

void BoxCollision2d::update(float deltaTime)
{
    std::map<dis::ivec2, GameObject *> objects = Scene::getInstance().boxCollision2dController->objects;

    dis::ivec2 left = dis::ivec2((int)floor(this->object->transform.position.x - 1.0f), (int)floor(this->object->transform.position.y));
    dis::ivec2 right = dis::ivec2((int)floor(this->object->transform.position.x + 1.0f), (int)floor(this->object->transform.position.y));
    dis::ivec2 up = dis::ivec2((int)floor(this->object->transform.position.x), (int)floor(this->object->transform.position.y + 1.0f));
    dis::ivec2 down = dis::ivec2((int)floor(this->object->transform.position.x), (int)floor(this->object->transform.position.y - 1.0f));

    if ((objects.find(left) != objects.end()) || (objects.find(right) != objects.end()) || (objects.find(up) != objects.end()) || (objects.find(down) != objects.end()))
    {
        isColliding(objects[left]);
    }
    
}


void BoxCollision2d::isColliding(GameObject *other)
{
    if (this->object->transform.position.x < other->transform.position.x + 1.0f &&
        this->object->transform.position.x + 1.0f > other->transform.position.x &&
        this->object->transform.position.y < other->transform.position.y + 1.0f &&
        this->object->transform.position.y + 1.0f > other->transform.position.y)
    {
        std::cout << "Collision" << std::endl;
    }
}

void BoxCollision2d::setGameObject(GameObject *gameObject)
{
    this->object = gameObject;
}