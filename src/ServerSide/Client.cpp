#include "Client.hpp"
#include <sstream>

Client::Client()
{
    tcpConnection = new TcpConnection(_players, _serverFd);
    udpConnection = new UdpConnection(_players, _serverFd);
}

void Client::renderPlayers()
{
    for (const auto &player : _players)
    {
        player.second->gameObject->update(0);
    }
}