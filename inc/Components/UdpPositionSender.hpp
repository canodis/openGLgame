#pragma once

#include "Component.hpp"
#include "Client.hpp"

class UdpPositionSender : public Component
{
public:
    UdpPositionSender();
    UdpPositionSender(GameObject *gameObject);
    ~UdpPositionSender() override;
    void update(float deltaTime) override;
    void setGameObject(GameObject *gameObject) override;
    void setStatic() override;
private:
    glm::vec3 lastPosition;
    GameObject *gameObject;
};