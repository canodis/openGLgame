#include "UdpConnection.hpp"

UdpConnection::UdpConnection(std::map<int, ServerPlayer *> &players, int &serverFd) : _players(players), _serverFd(serverFd), _accumulatedTime(0)
{
    _initSocket();
    _udpThread = std::thread(&UdpConnection::_threadFunc, this);
    _tickRate = 1.0 / 60;
}

UdpConnection::~UdpConnection()
{
}

void UdpConnection::sendUdpMessage(const char *message)
{
    sendto(_udpSocket, message, strlen(message), 0, (struct sockaddr *)&_serverUdpAddr, sizeof(_serverUdpAddr));
}

void UdpConnection::sendPlayerPosition(float x, float y, float deltaTime)
{
    if (_serverFd == -1)
        return;
    _accumulatedTime += deltaTime;
    if (_accumulatedTime >= _tickRate)
    {
        char buffer[101];
        sprintf(buffer, "%d %f %f", _serverFd, x, y);
        sendUdpMessage(buffer);
        _accumulatedTime = 0;
    }
}

void UdpConnection::sendPlayerAllData(float x, float y, int scaleX, int animation, float deltaTime)
{
    if (_serverFd == -1)
        return;
    _accumulatedTime += deltaTime;
    if (_accumulatedTime >= _tickRate)
    {
        char buffer[101];
        sprintf(buffer, "%d %f %f %d %d", _serverFd, x, y, scaleX, animation);
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

    int reuse = 1;
    if (setsockopt(_udpSocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0)
    {
        std::cout << "Error setting UDP socket options" << std::endl;
        exit(1);
    }

    memset(&_clientUdpAddr, 0, sizeof(_clientUdpAddr));
    _clientUdpAddr.sin_family = AF_INET;
    _clientUdpAddr.sin_port = htons(CLIENT_UDP_PORT);
    _clientUdpAddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(_udpSocket, (struct sockaddr *)&_clientUdpAddr, sizeof(_clientUdpAddr)) < 0)
    {
        std::cout << "Error binding UDP socket: " << strerror(errno) << std::endl;
        exit(1);
    }

    memset(&_serverUdpAddr, 0, sizeof(_serverUdpAddr));
    _serverUdpAddr.sin_family = AF_INET;
    _serverUdpAddr.sin_port = htons(SERVER_UDP_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &_serverUdpAddr.sin_addr) <= 0)
    {
        std::cout << "Error converting IP address" << std::endl;
        exit(1);
    }
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
    float x, y;
    int scaleX, animation;
    std::istringstream iss(msg);

    iss >> fd;
    iss >> x;
    iss >> y;
    iss >> scaleX;
    iss >> animation;
    std::map<int, ServerPlayer *>::iterator it = _players.find(fd);
    if (it == _players.end())
    {
        _createPlayer(fd, x, y);
    }
    else
    {
        it->second->SetPosition(x, y);
        it->second->SetScale(scaleX);
        it->second->SetAnimation(animation);
    }
}

void UdpConnection::_createPlayer(int fd, int x, int y)
{
    _players.insert(std::pair<int, ServerPlayer *>(fd, new ServerPlayer(fd, x, y)));
}
