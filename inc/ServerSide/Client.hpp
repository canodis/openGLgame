#pragma once

# define SERVER_IP "45.87.173.55"

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
    void sendTcpMessage(const char *message);
    void sendUdpMessage(const char *message);
    void sendPlayerPosition(float x, float y, float deltaTime);
    void renderPlayers();
private:
    float _accumulatedTime;
    std::map<int, ServerPlayer *> _players;
    Client();
    int _serverFd;
    int _tcpSocket;
    int _udpSocket;
    struct sockaddr_in _tcpAddr;
    struct sockaddr_in _clientUdpAddr;
    struct sockaddr_in _serverUdpAddr;
    void _initTcpSocket();
    void _initUdpSocket();
    void _tcpThreadFunc();
    void _udpThreadFunc();
    void _parseTcpMessage(const std::string &message);
    void _tcpLoginRequest(std::istringstream &iss);
    void _deletePlayer(int fd);
    std::thread _tcpThread;
    std::thread _udpThread;
};