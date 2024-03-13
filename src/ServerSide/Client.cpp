#include "Client.hpp"
#include <sstream>
#include "Scene.hpp"

Client::Client()
{
    tcpConnection = new TcpConnection(_players, _serverFd);
    udpConnection = new UdpConnection(_players, _serverFd);
}

void Client::renderPlayers(float deltaTime)
{
    for (const auto &player : _players)
    {
        player.second->update(deltaTime);
    }
}

void Client::handlePlayerPositionReq(std::istringstream &iss)
{
    float positionX, positionY, targetX, targetY;
    iss >> positionX >> positionY >> targetX >> targetY;
    Scene::getInstance().player->SetPosition(glm::vec3(positionX, positionY, 0));
    Scene::getInstance().player->SetTargetPosition(glm::vec3(targetX, targetY, 0));
}

void Client::terminate()
{
    tcpConnection->terminate();
    udpConnection->terminate();
}
