#include "BoxCollision2d.hpp"
#include "Scene.hpp"
#include "GravityComponent.hpp"

BoxCollision2d::BoxCollision2d()
{
    updateType = [this](float deltaTime) { this->dynamicUpdate(deltaTime); };
    collisionScale = glm::vec2(1.0f, 1.0f);
    for (int i = 0; i < 8; i++)
    {
        GameObject *obj = Scene::getInstance().gameObjectManager->Create2dObject("boxCollision2d");
        obj->SetTexture(Scene::getInstance().textureManager->loadTexture("./textures/white.png"));
        obj->SetShaderProgram(Scene::getInstance().shaderProgram);
        obj->SetColor(glm::vec4(0.0f, 0.7f, 0.0f, 0.4f));
        debugObjects.push_back(obj);
    }
}

BoxCollision2d::BoxCollision2d(GameObject *gameObject) : BoxCollision2d()
{
    this->object = gameObject;
}

void BoxCollision2d::update(float deltaTime)
{
    updateType(deltaTime);
}

void BoxCollision2d::dynamicUpdate(float deltaTime)
{
    std::map<dis::ivec2, GameObject *> objects = Scene::getInstance().boxCollision2dController->objects;
    objorigin = getOrigin(this->object);

    left = dis::ivec2(objorigin.x - 1.0f, objorigin.y);
    leftup = dis::ivec2(objorigin.x - 1.0f, objorigin.y + 1.0f);
    leftdown = dis::ivec2(objorigin.x - 1.0f, objorigin.y - 1.0f);
    right = dis::ivec2(objorigin.x + 1.0f, objorigin.y);
    rightup = dis::ivec2(objorigin.x + 1.0f, objorigin.y + 1.0f);
    rightdown = dis::ivec2(objorigin.x + 1.0f, objorigin.y - 1.0f);
    up = dis::ivec2(objorigin.x, objorigin.y + 1.0f);
    down = dis::ivec2(objorigin.x, objorigin.y - 1.0f);

    if ((objects.find(left) != objects.end()))
    {
        isColliding(objects[left]);
    }
    if ((objects.find(right) != objects.end()))
    {
        isColliding(objects[right]);
    }
    if ((objects.find(up) != objects.end()))
    {
        isColliding(objects[up]);
    }
    if ((objects.find(leftup) != objects.end()))
    {
        isColliding(objects[leftup]);
    }
    if ((objects.find(leftdown) != objects.end()))
    {
        isColliding(objects[leftdown]);
    }
    if ((objects.find(rightup) != objects.end()))
    {
        isColliding(objects[rightup]);
    }
    if ((objects.find(rightdown) != objects.end()))
    {
        isColliding(objects[rightdown]);
    }
    if ((objects.find(down) != objects.end()))
    {
        isColliding(objects[down]);
    }
    else
    {
        grounded(false);
    }
    drawDebugCollision();
}

void BoxCollision2d::staticUpdate(float deltaTime)
{

}

void BoxCollision2d::isColliding(GameObject *other)
{
    if (other->GetComponent<BoxCollision2d>() == nullptr)
        return;
    float overlapX, overlapY;

    if (this->object->transform.position.x<other->transform.position.x + collisionScale.x &&this->object->transform.position.x + collisionScale.x> other->transform.position.x &&
        this->object->transform.position.y<other->transform.position.y + collisionScale.y &&this->object->transform.position.y + collisionScale.y> other->transform.position.y)
    {
        overlapX = std::min(this->object->transform.position.x + collisionScale.x, other->transform.position.x + collisionScale.x) - std::max(this->object->transform.position.x, other->transform.position.x);
        overlapY = std::min(this->object->transform.position.y + collisionScale.y, other->transform.position.y + collisionScale.y) - std::max(this->object->transform.position.y, other->transform.position.y);

        overlapCalculation(other, overlapX, overlapY);
    }
}

void BoxCollision2d::overlapCalculation(GameObject *other, float &overlapX, float &overlapY)
{
    if (overlapX < overlapY)
    {
        if (this->object->transform.position.x < other->transform.position.x)
        {
            this->object->transform.position.x -= overlapX;
        }
        else
        {
            this->object->transform.position.x += overlapX;
        }
    }
    else
    {
        if (this->object->transform.position.y < other->transform.position.y)
        {
            this->object->transform.position.y -= overlapY;
            this->object->velocity.y = 0.0f;
        }
        else
        {
            this->object->transform.position.y += overlapY;
            grounded(true);
        }
    }
}

void BoxCollision2d::setGameObject(GameObject *gameObject)
{
    this->object = gameObject;
}

dis::ivec2 BoxCollision2d::getOrigin(GameObject *gameObject)
{
    float originx;
    float originy;
    if (gameObject->transform.position.x > 0)
        originx = gameObject->transform.position.x + collisionScale.x / 2;
    else
        originx = gameObject->transform.position.x - collisionScale.x / 2;
    if (gameObject->transform.position.y > 0)
        originy = gameObject->transform.position.y + collisionScale.y / 2;
    else
        originy = gameObject->transform.position.y - collisionScale.y / 2;
    return dis::ivec2(originx, originy);
}

void BoxCollision2d::drawDebugCollision()
{
    static bool &debug = Scene::getInstance().debug;
    if (!debug)
        return;

    debugObjects[0]->transform.position.x = left.x;
    debugObjects[0]->transform.position.y = left.y;
    debugObjects[1]->transform.position.x = right.x;
    debugObjects[1]->transform.position.y = right.y;
    debugObjects[2]->transform.position.x = up.x;
    debugObjects[2]->transform.position.y = up.y;
    debugObjects[3]->transform.position.x = down.x;
    debugObjects[3]->transform.position.y = down.y;
    debugObjects[4]->transform.position.x = leftup.x;
    debugObjects[4]->transform.position.y = leftup.y;
    debugObjects[5]->transform.position.x = leftdown.x;
    debugObjects[5]->transform.position.y = leftdown.y;
    debugObjects[6]->transform.position.x = rightup.x;
    debugObjects[6]->transform.position.y = rightup.y;
    debugObjects[7]->transform.position.x = rightdown.x;
    debugObjects[7]->transform.position.y = rightdown.y;

    for (auto &obj : debugObjects)
    {
        obj->update(0.0f);
    }
}

void BoxCollision2d::setCollisionScale(glm::vec2 scale)
{
    collisionScale = scale;
}

void BoxCollision2d::grounded(bool grounded)
{
    GravityComponent *gravity = this->object->GetComponent<GravityComponent>();
    if (gravity != nullptr)
    {
        gravity->setGrounded(grounded);
    }
}

void BoxCollision2d::setStatic()
{
    updateType = [this](float deltaTime) { this->staticUpdate(deltaTime); };
}


BoxCollision2d::~BoxCollision2d()
{
    for (auto& obj : debugObjects)
        delete obj;
}