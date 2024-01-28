#pragma once


# include <sys/socket.h>
# include <netinet/in.h>
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

# define SERVER_IP "45.87.173.55"
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
    void renderPlayers();
    TcpConnection *tcpConnection;
    UdpConnection *udpConnection;
private:
    std::map<int, ServerPlayer *> _players;
    int _serverFd;
    Client();
};