#pragma once

#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <sstream>
#include <map>
class UdpConnection;
#include "ServerPlayer.hpp"

# define SERVER_IP "45.87.173.55"
# define SERVER_UDP_PORT 8081
# define CLIENT_UDP_PORT 8082

class UdpConnection
{
public:
    UdpConnection(std::map<int, ServerPlayer *> &players, int &serverFd);
    ~UdpConnection();
    void sendUdpMessage(const char *message);
    void sendPlayerPosition(float x, float y, float deltaTime);
    void sendPlayerAllData(float x, float y, int scaleX, int animation, float deltaTime);
private:
    float _accumulatedTime;
    int _udpSocket;
    struct sockaddr_in _clientUdpAddr;
    struct sockaddr_in _serverUdpAddr;
    std::thread _udpThread;
    std::map<int, ServerPlayer *> &_players;
    int &_serverFd;
    float _tickRate;

    void _createPlayer(int fd, int x, int y);
    void _initSocket();
    void _threadFunc();
    void _playerPositionHandle(const std::string &msg);
};