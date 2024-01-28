#include "Client.hpp"
#include <sstream>

Client::Client() : _serverFd(-1), _accumulatedTime(0)
{
    _initTcpSocket();
    _initUdpSocket();
}

void Client::_initTcpSocket()
{
    _tcpSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_tcpSocket < 0)
    {
        std::cout << "Error creating TCP socket" << std::endl;
        exit(1);
    }
    memset(&_tcpAddr, 0, sizeof(_tcpAddr));
    _tcpAddr.sin_family = AF_INET;
    _tcpAddr.sin_port = htons(SERVER_TCP_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &_tcpAddr.sin_addr) <= 0)
    {
        std::cout << "Error converting IP address" << std::endl;
        exit(1);
    }
    if (connect(_tcpSocket, (struct sockaddr *)&_tcpAddr, sizeof(_tcpAddr)) < 0)
    {
        std::cout << "Error connecting to server" << std::endl;
        exit(1);
    }
    _tcpThread = std::thread(&Client::_tcpThreadFunc, this);
    _tcpThread.detach();
}

void Client::_initUdpSocket()
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

    _udpThread = std::thread(&Client::_udpThreadFunc, this);
    _udpThread.detach();
}

void Client::_tcpThreadFunc()
{
    char buffer[1024];
    while (true)
    {
        memset(buffer, 0, sizeof(buffer));
        if (recv(_tcpSocket, buffer, sizeof(buffer), 0) <= 0)
        {
            std::cout << "Server closed." << std::endl;
            exit(1);
        }
        _parseTcpMessage(buffer);
    }
}

void Client::_udpThreadFunc()
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
            char senderIP[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &senderAddr.sin_addr, senderIP, INET_ADDRSTRLEN);
            std::cout << "Udp message from " << senderIP << ":" << ntohs(senderAddr.sin_port) << " : " << buffer << std::endl;
        }
    }
}

void Client::sendTcpMessage(const char *message)
{
    if (send(_tcpSocket, message, strlen(message), 0) < 0)
    {
        std::cout << "Error sending data to server" << std::endl;
        exit(1);
    }
}

void Client::sendUdpMessage(const char *message)
{
    if (sendto(_udpSocket, message, strlen(message), 0, (struct sockaddr *)&_serverUdpAddr, sizeof(_serverUdpAddr)) < 0)
    {
        std::cout << "Error sending data to server" << std::endl;
        exit(1);
    }
}

void Client::sendPlayerPosition(float x, float y, float deltaTime)
{
    if (_serverFd == -1)
        return;
    _accumulatedTime += deltaTime;
    if (_accumulatedTime >= 1.0 / 30)
    {
        char buffer[1024];
        sprintf(buffer, "%d %f %f", _serverFd, x, y);
        sendUdpMessage(buffer);
        _accumulatedTime = 0;
    }
}

void Client::_parseTcpMessage(const std::string &message)
{
    std::size_t start = 0, end = 0;

    while ((start = message.find('/', start)) != std::string::npos)
    {
        end = message.find('*', start);
        if (end == std::string::npos)
        {
            break;
        }
        std::string substr = message.substr(start + 1, end - start - 1);
        if (substr.find("New") == 0)
        {
            std::istringstream ss(substr.substr(3));
            int new_fd;
            ss >> new_fd;
            _players.insert(std::pair<int, ServerPlayer *>(new_fd, new ServerPlayer(new_fd, 0, 0)));
        }
        else if (substr.find("Left") == 0)
        {
            std::istringstream ss(substr.substr(4));
            int fd;
            ss >> fd;
            _deletePlayer(fd);
        }
        else if (substr.find("Login") == 0)
        {
            std::istringstream ss(substr.substr(5));
            _tcpLoginRequest(ss);
        }
        start = end + 1;
    }
}

void Client::_tcpLoginRequest(std::istringstream &ss)
{
    int playerCount;
    int playerFd;

    ss >> playerCount;
    ss >> _serverFd;
    std::cout << "Server fd: " << _serverFd << std::endl;
    for (int i = 0; i < playerCount - 1; i++)
    {
        ss >> playerFd;
        _players.insert(std::pair<int, ServerPlayer *>(playerFd, new ServerPlayer(playerFd, 0, 0)));
    }
}

void Client::_deletePlayer(int fd)
{
    std::map<int, ServerPlayer *>::iterator it = _players.find(fd);
    if (it != _players.end())
    {
        delete it->second;
        _players.erase(it);
    }
}

void Client::renderPlayers()
{
    for (const auto &player : _players)
    {
        player.second->gameObject->Draw();
    }
}