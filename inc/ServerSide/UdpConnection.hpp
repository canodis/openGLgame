#pragma once

#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <sstream>
#include <map>
#include <functional>
class UdpConnection;
#include "ServerPlayer.hpp"

# define SERVER_IP "193.57.41.221"
# define SERVER_UDP_PORT 8081
# define CLIENT_UDP_PORT 8082

class UdpConnection
{
public:
    UdpConnection(std::map<int, ServerPlayer *> &players, int &serverFd);
    ~UdpConnection();
    void sendUdpMessage(const char *message);
    void sendPlayerAllData(Transform playerTransform, float x, float y, float deltaTime, bool forceSend = false);
    void connect();
    void disconnect();
private:
    float _accumulatedTime;
    int _udpSocket;
    int &_serverFd;
    float _tickRate;
    bool _udpIsRunning;
    struct sockaddr_in _clientUdpAddr;
    struct sockaddr_in _serverUdpAddr;
    std::thread _udpThread;
    std::map<int, ServerPlayer *> &_players;
    std::map<int, std::function<void(std::istringstream &)>> _udpPackageHandlers;

    void _connectSocket();
    void _handleResponse(std::istringstream iss);
    void _initResponseHandlers();
    ServerPlayer *_createPlayer(int fd, int x, int y);
    void _threadFunc();
    void _playerPositionHandle(std::istringstream &iss);
    void _pingHandle(std::istringstream &iss);
    void _serverShutDownHandle(std::istringstream &iss);
    void _handleNpcPosition(std::istringstream &iss);
};