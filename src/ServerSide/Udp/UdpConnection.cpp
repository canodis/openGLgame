#include "UdpConnection.hpp"
#include "PlayerPositionPackage.hpp"
#include <msgpack.hpp>
#include "BasePackage.hpp"
UdpConnection::UdpConnection(std::map<int, ServerPlayer *> &players, int &serverFd) : _players(players), _serverFd(serverFd), _accumulatedTime(0)
{
    _initResponseHandlers();
    _tickRate = 1.0 / 30;
}

UdpConnection::~UdpConnection() {}

void UdpConnection::sendUdpMessage(msgpack::sbuffer &sbuf)
{
    sendto(_udpSocket, sbuf.data(), sbuf.size(), 0, (struct sockaddr *)&_clientUdpAddr, sizeof(_clientUdpAddr));
}

void UdpConnection::sendPlayerAllData(const Transform &playerTransform, const float &targetX, const float &targetY)
{
    if (_serverFd == -1)
        return;
    PlayerPositionPackage playerPositionPackage(_serverFd, targetX, targetY, playerTransform.position.x, playerTransform.position.y);
    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, playerPositionPackage);
    sendUdpMessage(sbuf);
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
            _handleResponse(buffer);
        }
    }
    std::cout << "UDP thread ended" << std::endl;
}

void UdpConnection::_handleResponse(const char *buffer)
{
    try
    {
        msgpack::object_handle oh = msgpack::unpack(buffer, 1024);
        msgpack::object deserialized = oh.get();
        BasePackage basePacket;

        deserialized.convert(basePacket);
        if (_udpPackageHandlers.find(basePacket.packageId) != _udpPackageHandlers.end())
        {
            _udpPackageHandlers[basePacket.packageId](deserialized);
        }
        else
        {
            std::cout << "----------------------------------------" << std::endl;
            std::cout << "Unknown response type: " << basePacket.packageId << std::endl;
            std::cout << "----------------------------------------" << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void UdpConnection::terminate()
{
}