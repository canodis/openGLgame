#include "UdpConnection.hpp"
#include "Client.hpp"
#include "ServerPackages.hpp"

UdpConnection::UdpConnection(std::map<int, ServerPlayer *> &players, int &serverFd) : _players(players), _serverFd(serverFd), _accumulatedTime(0)
{
    _initResponseHandlers();
    _tickRate = 1.0 / 30;
}

UdpConnection::~UdpConnection() {}

void UdpConnection::sendUdpMessage(const char *message)
{
    sendto(_udpSocket, message, strlen(message), 0, (struct sockaddr *)&_clientUdpAddr, sizeof(_clientUdpAddr));
}

void UdpConnection::sendPlayerAllData(Transform playerTransform, float targetX, float targetY, float deltaTime, bool forceSend)
{
    if (_serverFd == -1)
        return;
    _accumulatedTime += deltaTime;
    if (_accumulatedTime >= _tickRate || forceSend)
    {
        char buffer[101];
        sprintf(buffer, "%d %d %f %f %f %f ", (int)ServerPackage::PositionRequest, _serverFd,
                playerTransform.position.x, playerTransform.position.y, targetX, targetY);
        sendUdpMessage(buffer);
        _accumulatedTime = 0;
    }
}

void UdpConnection::_connectSocket()
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

void UdpConnection::connect()
{
    _connectSocket();
    _udpIsRunning = true;
    _udpThread = std::thread(&UdpConnection::_threadFunc, this);
}

void UdpConnection::disconnect()
{
    if (_udpThread.joinable())
    {
        _udpThread.join();
    }
    close(_udpSocket);
}

void UdpConnection::_threadFunc()
{
    char buffer[1024];
    struct sockaddr_in senderAddr;

    socklen_t senderAddrLen = sizeof(senderAddr);
    while (_udpIsRunning)
    {
        if (recvfrom(_udpSocket, buffer, sizeof(buffer), 0, (struct sockaddr *)&senderAddr, &senderAddrLen) < 0)
        {
            std::cout << "Error receiving data from server" << std::endl;
        }
        else
        {
            _handleResponse(std::istringstream(buffer));
        }
    }
    std::cout << "UDP thread ended" << std::endl;
}

void UdpConnection::_handleResponse(std::istringstream iss)
{
    int responseType;
    iss >> responseType;
    if (_udpPackageHandlers.find(responseType) != _udpPackageHandlers.end())
    {
        _udpPackageHandlers[responseType](iss);
    }
    else
    {
        std::cout << "Unknown response type: " << responseType << std::endl;
    }
}

void UdpConnection::_playerPositionHandle(std::istringstream &iss)
{
    int fd;
    float targetX, targetY;
    float positionX, positionY;
    int animation;

    iss >> fd >> positionX >> positionY >> targetX >> targetY;
    std::lock_guard<std::mutex> lock(Client::getInstance()._playerMutex);
    std::map<int, ServerPlayer *>::iterator it = _players.find(fd);
    if (it == _players.end())
    {
        std::cout << "Player not found, creating new one" << std::endl;
        _createPlayer(fd, positionX, positionY)->SetTargetPosition(positionX, positionY, targetX, targetY);
    }
    else
    {
        it->second->SetTargetPosition(positionX, positionY, targetX, targetY);
    }
}

ServerPlayer *UdpConnection::_createPlayer(int fd, int x, int y)
{
    std::lock_guard<std::mutex> lock(Client::getInstance()._playerMutex);
    ServerPlayer *player = new ServerPlayer(fd, x, y);
    _players.insert(std::pair<int, ServerPlayer *>(fd, player));
    return player;
}

void UdpConnection::_initResponseHandlers()
{
    _udpPackageHandlers[(int)ServerPackage::PositionRequest] = std::bind(&UdpConnection::_playerPositionHandle, this, std::placeholders::_1);
    _udpPackageHandlers[(int)ServerPackage::Ping] = std::bind(&UdpConnection::_pingHandle, this, std::placeholders::_1);
    _udpPackageHandlers[(int)ServerPackage::ServerShutDown] = std::bind(&UdpConnection::_serverShutDownHandle, this, std::placeholders::_1);
}

void UdpConnection::_pingHandle(std::istringstream &iss) {}

void UdpConnection::_serverShutDownHandle(std::istringstream &iss)
{
    std::cout << "Server shut down" << std::endl;
    std::lock_guard<std::mutex> lock(Client::getInstance()._playerMutex);
    _udpIsRunning = false;
    for (const auto &player : _players)
    {
        delete player.second;
    }
    _players.clear();
}   