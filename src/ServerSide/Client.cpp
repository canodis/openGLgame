#include "Client.hpp"
#include <sstream>

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
