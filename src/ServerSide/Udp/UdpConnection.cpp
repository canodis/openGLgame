#include "UdpConnection.hpp"
#include "PlayerPositionPackage.hpp"
#include <msgpack.hpp>

UdpConnection::UdpConnection(std::map<int, ServerPlayer *> &players, int &serverFd) : _players(players), _serverFd(serverFd), _accumulatedTime(0)
{
    _initResponseHandlers();
    _tickRate = 1.0 / 30;
}

UdpConnection::~UdpConnection() {}

void UdpConnection::sendUdpMessage(const std::string &data)
{
    sendto(_udpSocket, data.c_str(), data.size(), 0, (struct sockaddr *)&_clientUdpAddr, sizeof(_clientUdpAddr));
}

void UdpConnection::sendPlayerAllData(const Transform &playerTransform, const float &targetX, const float &targetY)
{
    if (_serverFd == -1)
        return;
    PlayerPositionPackage playerPositionPackage(_serverFd, playerTransform.position.x, playerTransform.position.y, targetX, targetY);
    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, playerPositionPackage);
    std::string rawData(sbuf.data(), sbuf.size());
    sendUdpMessage(rawData);
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
        bzero(buffer, sizeof(buffer));
        if (recvfrom(_udpSocket, buffer, sizeof(buffer), 0, (struct sockaddr *)&senderAddr, &senderAddrLen) < 0)
        {
            std::cout << "Error receiving data from server" << std::endl;
        }
        else
        {
            _handleResponse(std::string(buffer));
        }
    }
    std::cout << "UDP thread ended" << std::endl;
}

void UdpConnection::_handleResponse(const std::string &rawData)
{
    msgpack::object_handle oh = msgpack::unpack(rawData.data(), rawData.size());
    msgpack::object deserialized = oh.get();
    BasePacket basePacket;
    deserialized.convert(basePacket);
    if (_udpPackageHandlers.find(basePacket.packetId) != _udpPackageHandlers.end())
    {
        _udpPackageHandlers[basePacket.packetId](deserialized);
    }
    else
    {
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "Unknown response type: " << basePacket.packetId << std::endl;
        std::cout << "----------------------------------------" << std::endl;
    }
}

void UdpConnection::terminate()
{
}