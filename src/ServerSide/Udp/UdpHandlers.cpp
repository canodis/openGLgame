#include "UdpConnection.hpp"
#include "Client.hpp"
#include "ServerPackages.hpp"
#include "NpcController.hpp"
#include "PlayerPositionPackage.hpp"

void UdpConnection::_initResponseHandlers()
{
    _udpPackageHandlers[(int)ServerPackage::PositionRequest] = std::bind(&UdpConnection::_playerPositionHandle, this, std::placeholders::_1);
    _udpPackageHandlers[(int)ServerPackage::Ping] = std::bind(&UdpConnection::_pingHandle, this, std::placeholders::_1);
    _udpPackageHandlers[(int)ServerPackage::ServerShutDown] = std::bind(&UdpConnection::_serverShutDownHandle, this, std::placeholders::_1);
    _udpPackageHandlers[(int)ServerPackage::BasicNpcPosition] = std::bind(&UdpConnection::_handleNpcPosition, this, std::placeholders::_1);
    _udpPackageHandlers[(int)ServerPackage::NewBasicNpc] = std::bind(&UdpConnection::_handleNewNpc, this, std::placeholders::_1);
}

void UdpConnection::_pingHandle(msgpack::object &rawPacket) {}

void UdpConnection::_serverShutDownHandle(msgpack::object &rawPacket)
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

void UdpConnection::_handleNewNpc(msgpack::object &rawPacket)
{
    NewBasicNpcPackage packet;
    rawPacket.convert(packet);
    NpcController::getInstance().handleNewBasicNpc(packet);
}

void UdpConnection::_handleNpcPosition(msgpack::object &rawPacket)
{
    BasicNpcPositionPackage packet;
    rawPacket.convert(packet);
    NpcController::getInstance().handleBasicNpcPosition(packet);
}

void UdpConnection::_playerPositionHandle(msgpack::object &rawPacket)
{
    PlayerPositionPackage packet;
    rawPacket.convert(packet);
    std::lock_guard<std::mutex> lock(Client::getInstance()._playerMutex);
    std::map<int, ServerPlayer *>::iterator it = _players.find(packet.fd);
    if (packet.fd == _serverFd)
    {
        Scene::getInstance().player->SetTargetPosition(packet.targetX, packet.targetY);
        Scene::getInstance().player->SetPosition(packet.positionX, packet.positionY);
        return;
    }
    if (it == _players.end())
    {
        std::cout << "Player not found with fd : " << packet.fd << std::endl;
    }
    else
    {
        it->second->SetTargetPosition(packet.positionX, packet.positionY, packet.targetX, packet.targetY);
    }
}
