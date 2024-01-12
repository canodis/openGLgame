#include "BoxCollision2d.hpp"
#include "Scene.hpp"

void BoxCollision2d::update(float deltaTime)
{
    std::map<dis::ivec2, GameObject *> objects = Scene::getInstance().boxCollision2dController->objects;
    // check 4 side of the object

    // // check left
    // dis::ivec2 left = dis::ivec2(this->object->transform.position.x - 1, this->object->transform.position.y);
    // if (objects.find(left) != objects.end())
    // {
    //     std::cout << "left" << std::endl;
    //     this->object->velocity.x = 0;
    // }
    // check bottom
    if (this->object->velocity.x >= 0)
    {
        dis::ivec2 bottom = dis::ivec2(round(this->object->transform.position.x - 0.5f), round(this->object->transform.position.y - 0.5f));
        if (objects.find(bottom) != objects.end())
        {
            std::cout << "bottom" << std::endl;
            this->object->velocity.y = 0;
            this->object->transform.position.y = bottom.y + 1;
        }
    }
    else
    {
        dis::ivec2 bottom = dis::ivec2(round(this->object->transform.position.x + 0.5f), round(this->object->transform.position.y - 0.5f));
        if (objects.find(bottom) != objects.end())
        {
            std::cout << "bottom" << std::endl;
            this->object->velocity.y = 0;
            this->object->transform.position.y = bottom.y + 1;
        }
    }

    // check right
    // dis::ivec2 right = dis::ivec2(this->object->transform.position.x + 1, this->object->transform.position.y);
    // if (objects.find(right) != objects.end())
    // {
    //     std::cout << "right" << std::endl;
    //     this->object->velocity.x = 0;
    // }
    // // check top
    // dis::ivec2 top = dis::ivec2(this->object->transform.position.x, this->object->transform.position.y + 1);
    // if (objects.find(top) != objects.end())
    // {
    //     std::cout << "top" << std::endl;
    //     this->object->transform.position.y = top.y - 1;
    // }
}

void BoxCollision2d::setGameObject(GameObject *gameObject)
{
    this->object = gameObject;
}