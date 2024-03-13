#pragma once

class Client;

# include <sys/socket.h>
# include <netinet/in.h>
# include <mutex>
# include <arpa/inet.h>
# include <unistd.h>
# include <string.h>
# include <iostream>
# include <stdlib.h>
# include <thread>
# include <map>
# include <sstream>
# include "ServerPlayer.hpp"
# include "TcpConnection.hpp"
# include "UdpConnection.hpp"

# define SERVER_IP "37.247.108.252"
# define SERVER_TCP_PORT 8080
# define SERVER_UDP_PORT 8081
# define CLIENT_UDP_PORT 8082

class Client
{
public:
    static Client &getInstance()
    {
        static Client instance;
        return instance;
    }
    void renderPlayers(float deltaTime);
    void handlePlayerPositionReq(std::istringstream &iss);
    void terminate();
    TcpConnection *tcpConnection;
    UdpConnection *udpConnection;
    std::mutex _playerMutex;
    std::mutex _npcMutex;
    int _serverFd;
private:
    std::map<int, ServerPlayer *> _players;
    Client();
};