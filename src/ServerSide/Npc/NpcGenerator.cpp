#include "NpcGenerator.hpp"

NpcGenerator::NpcGenerator()
{
}

NpcGenerator::~NpcGenerator()
{
}

Npc *NpcGenerator::generateNpc(int type)
{
    Npc *npc = nullptr;
    switch (type)
    {
    case NpcType::WhiteCat:
        npc = generateWhiteCat();
        break;
    case NpcType::CalicoCat:
        npc = generateCalicoCat();
        break;
    case NpcType::GhostCat:
        npc = generateGhostCat();
        break;
    case NpcType::RadioactiveCat:
        npc = generateRadioactiveCat();
        break;
    default:
        break;
    }
    return npc;
}

Npc *NpcGenerator::generateWhiteCat()
{
    Npc *npc = new BasicNpc();
    npc->obj = Scene::getInstance().gameObjectManager->Create2dObject("player");
    npc->obj->SetTexture(Scene::getInstance().textureManager->loadTexture("./textures/ana.jpeg"));
    npc->obj->SetShaderProgram(Scene::getInstance().shaderProgram);
    npc->obj->transform.position = glm::vec3(0);
    Animator *anim = npc->obj->AddComponent<Animator>();
    Animation *an = anim->loadTexturesFromDirectory(AnimationType::idle, "./animations/WhiteCat/Idle/", "catIdle", "png", 0.2f);
    an->loop = false;
    anim->loadTexturesFromDirectory(AnimationType::run, "./animations/WhiteCat/Run/", "catRun", "png", 0.2f);
    anim->setCurrentAnimation(AnimationType::idle);

    return npc;
}

Npc *NpcGenerator::generateCalicoCat()
{
    Npc *npc = new BasicNpc();
    npc->obj = Scene::getInstance().gameObjectManager->Create2dObject("player");
    npc->obj->SetTexture(Scene::getInstance().textureManager->loadTexture("./textures/ana.jpeg"));
    npc->obj->SetShaderProgram(Scene::getInstance().shaderProgram);
    npc->obj->transform.position = glm::vec3(0);
    Animator *anim = npc->obj->AddComponent<Animator>();
    Animation *an = anim->loadTexturesFromDirectory(AnimationType::idle, "./animations/CalicoCat/Idle/", "calicoIdle", "png", 0.2f);
    an->loop = false;
    anim->loadTexturesFromDirectory(AnimationType::run, "./animations/CalicoCat/Run/", "calicoRun", "png", .15f);
    anim->setCurrentAnimation(AnimationType::idle);

    return npc;
}

Npc *NpcGenerator::generateGhostCat()
{
    Npc *npc = new BasicNpc();
    npc->obj = Scene::getInstance().gameObjectManager->Create2dObject("player");
    npc->obj->SetTexture(Scene::getInstance().textureManager->loadTexture("./textures/ana.jpeg"));
    npc->obj->SetShaderProgram(Scene::getInstance().shaderProgram);
    npc->obj->transform.position = glm::vec3(0);
    Animator *anim = npc->obj->AddComponent<Animator>();
    Animation *an = anim->loadTexturesFromDirectory(AnimationType::idle, "./animations/GhostCat/Idle/", "ghostIdle", "png", 0.2f);
    an->loop = false;
    anim->loadTexturesFromDirectory(AnimationType::run, "./animations/GhostCat/Run/", "ghostRun", "png", 0.2f);
    anim->setCurrentAnimation(AnimationType::idle);

    return npc;
}

Npc *NpcGenerator::generateRadioactiveCat()
{
    Npc *npc = new BasicNpc();
    npc->obj = Scene::getInstance().gameObjectManager->Create2dObject("player");
    npc->obj->SetTexture(Scene::getInstance().textureManager->loadTexture("./textures/ana.jpeg"));
    npc->obj->SetShaderProgram(Scene::getInstance().shaderProgram);
    npc->obj->transform.position = glm::vec3(0);
    Animator *anim = npc->obj->AddComponent<Animator>();
    Animation *an = anim->loadTexturesFromDirectory(AnimationType::idle, "./animations/RadioactiveCat/Idle/", "radioactiveIdle", "png", 0.2f);
    an->loop = false;
    anim->loadTexturesFromDirectory(AnimationType::run, "./animations/RadioactiveCat/Run/", "radioactiveRun", "png", 0.2f);
    anim->setCurrentAnimation(AnimationType::idle);

    return npc;
}