#include "NpcGenerator.hpp"

NpcGenerator::NpcGenerator() { }

NpcGenerator::~NpcGenerator() { }

Npc *NpcGenerator::generateNpc(int type, float speed)
{
    Npc *npc = nullptr;
    switch (type)
    {
    case NpcType::WhiteCat:
        npc = generateWhiteCat(speed);
        break;
    case NpcType::CalicoCat:
        npc = generateCalicoCat(speed);
        break;
    case NpcType::GhostCat:
        npc = generateGhostCat(speed);
        break;
    case NpcType::RadioactiveCat:
        npc = generateRadioactiveCat(speed);
        break;
    case NpcType::Turret:
        npc = generateTurret();
        break;
    default:
        break;
    }
    return npc;
}

Npc *NpcGenerator::generateWhiteCat(float speed)
{
    Npc *npc = generateBasicNpcTemplate("./textures/ana.jpeg");
    Animator *animator = npc->obj->AddComponent<Animator>();
    Animation *anim = animator->loadTexturesFromDirectory(AnimationType::idle, "./animations/WhiteCat/Idle/", "catIdle", "png", speed / 30.0f);
    anim->loop = false;
    animator->loadTexturesFromDirectory(AnimationType::run, "./animations/WhiteCat/Run/", "catRun", "png", speed / 30.0f);
    animator->setCurrentAnimation(AnimationType::idle);
    return npc;
}

Npc *NpcGenerator::generateCalicoCat(float speed)
{
    Npc *npc = generateBasicNpcTemplate("./textures/ana.jpeg");
    Animator *animator = npc->obj->AddComponent<Animator>();
    Animation *anim = animator->loadTexturesFromDirectory(AnimationType::idle, "./animations/CalicoCat/Idle/", "calicoIdle", "png", speed / 30.0f);
    anim->loop = false;
    animator->loadTexturesFromDirectory(AnimationType::run, "./animations/CalicoCat/Run/", "calicoRun", "png", speed / 30.0f);
    animator->setCurrentAnimation(AnimationType::idle);

    return npc;
}

Npc *NpcGenerator::generateGhostCat(float speed)
{
    Npc *npc = generateBasicNpcTemplate("./textures/ana.jpeg");
    Animator *animator = npc->obj->AddComponent<Animator>();
    Animation *anim = animator->loadTexturesFromDirectory(AnimationType::idle, "./animations/GhostCat/Idle/", "ghostIdle", "png", speed / 30.0f);
    anim->loop = false;
    animator->loadTexturesFromDirectory(AnimationType::run, "./animations/GhostCat/Run/", "ghostRun", "png", speed / 30.0f);
    animator->setCurrentAnimation(AnimationType::idle);

    return npc;
}

Npc *NpcGenerator::generateRadioactiveCat(float speed)
{
    Npc *npc = generateBasicNpcTemplate("./textures/ana.jpeg");
    Animator *animator = npc->obj->AddComponent<Animator>();
    Animation *anim = animator->loadTexturesFromDirectory(AnimationType::idle, "./animations/RadioactiveCat/Idle/", "radioactiveIdle", "png", speed / 30.0f);
    anim->loop = false;
    animator->loadTexturesFromDirectory(AnimationType::run, "./animations/RadioactiveCat/Run/", "radioactiveRun", "png", speed / 30.0f);
    animator->setCurrentAnimation(AnimationType::idle);

    return npc;
}

Npc *NpcGenerator::generateTurret()
{
    Npc *npc = new TurretNpc();
    npc->obj = Scene::getInstance().gameObjectManager->CreateRectangle();
    npc->obj->SetTexture(Scene::getInstance().textureManager->loadTexture("./textures/turret.png"));
    npc->obj->SetShaderProgram(Scene::getInstance().shaderProgram);
    npc->obj->transform.position = glm::vec3(0);
    return npc;
}

Npc *NpcGenerator::generateBasicNpcTemplate(std::string texture)
{
    Npc *npc = new BasicNpc();
    npc->obj = Scene::getInstance().gameObjectManager->CreateRectangle();
    npc->obj->SetTexture(Scene::getInstance().textureManager->loadTexture(texture));
    npc->obj->SetShaderProgram(Scene::getInstance().shaderProgram);
    npc->obj->transform.position = glm::vec3(0);
    return npc;
}