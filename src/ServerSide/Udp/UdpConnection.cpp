#include "UdpConnection.hpp"

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
