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
#include "BasePackage.hpp"
#include "ServerPlayer.hpp"
#include "ServerPackages.hpp"
#include "Client.hpp"
#include "Npc.hpp"

# define SERVER_IP "37.247.108.252"
# define SERVER_UDP_PORT 8081
# define CLIENT_UDP_PORT 8082

class UdpConnection
{
public:
    UdpConnection(std::map<int, ServerPlayer *> &players, int &serverFd);
    ~UdpConnection();
    void sendUdpMessage(const std::string &data, int size);
    void sendPlayerAllData(const Transform &playerTransform, const float &x, const float &y);
    void connect();
    void disconnect();
    void terminate();
    Npc *turrets;
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
    std::map<int, std::function<void(msgpack::object &)>> _udpPackageHandlers;

    void _connectSocket();
    void _handleResponse(const char *rawData);
    ServerPlayer *_createPlayer(int fd, int x, int y);
    void _threadFunc();

    //handlers

    void _initResponseHandlers();
    void _playerPositionHandle(msgpack::object &rawPacket);
    void _pingHandle(msgpack::object &rawPacket);
    void _serverShutDownHandle(msgpack::object &rawPacket);
    void _handleNpcPosition(msgpack::object &rawPacket);
    void _handleNewNpc(msgpack::object &rawPacket);

    
};