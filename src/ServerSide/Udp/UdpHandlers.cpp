#include "UdpConnection.hpp"
#include "Client.hpp"
#include "ServerPackages.hpp"
#include "NpcController.hpp"

void UdpConnection::_initResponseHandlers()
{
    _udpPackageHandlers[(int)ServerPackage::PositionRequest] = std::bind(&UdpConnection::_playerPositionHandle, this, std::placeholders::_1);
    _udpPackageHandlers[(int)ServerPackage::Ping] = std::bind(&UdpConnection::_pingHandle, this, std::placeholders::_1);
    _udpPackageHandlers[(int)ServerPackage::ServerShutDown] = std::bind(&UdpConnection::_serverShutDownHandle, this, std::placeholders::_1);
    _udpPackageHandlers[(int)ServerPackage::BasicNpcRequest] = std::bind(&UdpConnection::_handleNpcPosition, this, std::placeholders::_1);
}

void UdpConnection::_pingHandle(std::istringstream &iss) {}

void UdpConnection::_serverShutDownHandle(std::istringstream &iss)
{
    std::cout << "Server shut down" << std::endl;
    std::lock_guard<std::mutex> lock(Client::getInstance()._playerMutex);
    _udpIsRunning = false;
    for (const auto &player : _players)
    {
        delete player.second;
    }
    _players.clear();
}

void UdpConnection::_handleNpcPosition(std::istringstream &iss)
{
    NpcController::getInstance().handleNpcPositionReq(iss);
}

void UdpConnection::_playerPositionHandle(std::istringstream &iss)
{
    int fd;
    float targetX, targetY;
    float positionX, positionY;
    int animation;

    iss >> fd >> positionX >> positionY >> targetX >> targetY;
    std::lock_guard<std::mutex> lock(Client::getInstance()._playerMutex);
    std::map<int, ServerPlayer *>::iterator it = _players.find(fd);
    if (fd == _serverFd)
    {
        Scene::getInstance().player->SetTargetPosition(targetX, targetY);
        Scene::getInstance().player->SetPosition(positionX, positionY);
        return;
    }
    if (it == _players.end())
    {
        std::cout << "Player not found with fd : " << fd << std::endl;
    }
    else
    {
        it->second->SetTargetPosition(positionX, positionY, targetX, targetY);
    }
}
