#pragma once

#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <sstream>
#include <map>
#include "ServerPlayer.hpp"

# define SERVER_IP "45.87.173.55"
# define SERVER_TCP_PORT 8080

class TcpConnection
{
public:
    TcpConnection(std::map<int, ServerPlayer *> &players, int &serverFd);
    ~TcpConnection();
    void sendTcpMessage(const char *message);
    void sendPlayerPosition(float x, float y, float deltaTime);
private:
    int _tcpSocket;
    struct sockaddr_in _tcpAddr;
    std::thread _tcpThread;
    std::map<int, ServerPlayer *> &_players;
    int _serverFd;
    float _accumulatedTime;

    void _initSocket();
    void _ThreadFunc();
    void _parse(const std::string &message);
    void _loginRequest(std::istringstream &iss);
    void _deletePlayer(int fd);
};