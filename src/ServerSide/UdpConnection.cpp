#include "UdpConnection.hpp"
#include "Client.hpp"

UdpConnection::UdpConnection(std::map<int, ServerPlayer *> &players, int &serverFd) : _players(players), _serverFd(serverFd), _accumulatedTime(0)
{
    _initSocket();
    _udpThread = std::thread(&UdpConnection::_threadFunc, this);
    _tickRate = 1.0 / 30;
}

UdpConnection::~UdpConnection()
{
}

void UdpConnection::sendUdpMessage(const char *message)
{
    sendto(_udpSocket, message, strlen(message), 0, (struct sockaddr *)&_clientUdpAddr, sizeof(_clientUdpAddr));
}

void UdpConnection::sendPlayerPosition(float x, float y, float deltaTime)
{
    if (_serverFd == -1)
        return;
    _accumulatedTime += deltaTime;
    if (_accumulatedTime >= _tickRate)
    {
        char buffer[101];
        sprintf(buffer, "%d %f %f ", _serverFd, x, y);
        sendUdpMessage(buffer);
        _accumulatedTime = 0;
    }
}

void UdpConnection::sendPlayerAllData(float targetX, float targetY, float deltaTime, bool forceSend)
{
    if (_serverFd == -1)
        return;
    _accumulatedTime += deltaTime;
    if (_accumulatedTime >= _tickRate || forceSend)
    {
        char buffer[101];
        sprintf(buffer, "%d %f %f ", _serverFd, targetX, targetY);
        sendUdpMessage(buffer);
        _accumulatedTime = 0;
    }
}

void UdpConnection::_initSocket()
{
    _udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (_udpSocket < 0)
    {
        std::cout << "Error creating UDP socket" << std::endl;
        exit(1);
    }

    memset(&_clientUdpAddr, 0, sizeof(_clientUdpAddr));

    _clientUdpAddr.sin_family = AF_INET;
    _clientUdpAddr.sin_port = htons(SERVER_UDP_PORT);
    _clientUdpAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
}

void UdpConnection::_threadFunc()
{
    char buffer[1024];
    struct sockaddr_in senderAddr;
    socklen_t senderAddrLen = sizeof(senderAddr);
    while (true)
    {
        if (recvfrom(_udpSocket, buffer, sizeof(buffer), 0, (struct sockaddr *)&senderAddr, &senderAddrLen) < 0)
        {
            std::cout << "Error receiving data from server" << std::endl;
        }
        else
        {
            _playerPositionHandle(buffer);
        }
    }
}

void UdpConnection::_playerPositionHandle(const std::string &msg)
{
    int fd;
    float targetX, targetY;
    int animation;
    std::istringstream iss(msg);

    iss >> fd;
    iss >> targetX;
    iss >> targetY;
    std::lock_guard<std::mutex> lock(Client::getInstance()._playerMutex);
    std::map<int, ServerPlayer *>::iterator it = _players.find(fd);
    if (it == _players.end())
    {
        _createPlayer(fd, 0, 0);
    }
    else
    {
        it->second->SetTargetPosition(targetX, targetY);
    }
}

void UdpConnection::_createPlayer(int fd, int x, int y)
{
    std::lock_guard<std::mutex> lock(Client::getInstance()._playerMutex);
    _players.insert(std::pair<int, ServerPlayer *>(fd, new ServerPlayer(fd, x, y)));
}
