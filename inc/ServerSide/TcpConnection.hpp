#pragma once

class TcpConnection;
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <sstream>
#include <map>
#include "ServerPlayer.hpp"
#include "Client.hpp"
#define GUARD "6663131"

class TcpConnection
{
public:
    TcpConnection(std::map<int, ServerPlayer *> &players, int &serverFd);
    ~TcpConnection();
    void sendTcpMessage(const char *message);
    void sendPlayerNew(const Player &player);
private:
    std::string _buffer;
    int _tcpSocket;
    struct sockaddr_in _tcpAddr;
    std::thread _tcpThread;
    std::thread _connectionHandleThread;
    std::map<int, ServerPlayer *> &_players;
    std::map<int, std::function<void(std::istringstream &)>> _tcpPackageHandlers;
    int &_serverFd;
    float _accumulatedTime;

    bool _connectSocket();
    void _listen();
    void _tcpConnectionController();
    void _handleResponse(const std::string &message);
    void _animationRequest(std::istringstream &ss);

    // handlers
    void _initResponseHandlers();
    void _newPlayerHandle(std::istringstream &iss);
    void _playerLeftHandle(std::istringstream &iss);
    void _playerLoginHandle(std::istringstream &iss);

    void _handleNewTurret(std::istringstream &iss);
    void _handleTurretShoot(std::istringstream &iss);
    void _handleTurretDestroy(std::istringstream &iss);
    void _handleTurretHit(std::istringstream &iss);
    void _npcDie(std::istringstream &iss);
};