#include "TcpConnection.hpp"

TcpConnection::TcpConnection(std::map<int, ServerPlayer *> &players, int &serverFd) : _players(players), _serverFd(serverFd)
{
    _accumulatedTime = 0;
    _initSocket();
    _tcpThread = std::thread(&TcpConnection::_ThreadFunc, this);
    _tcpThread.detach();
}

TcpConnection::~TcpConnection()
{
    close(_tcpSocket);
}

void TcpConnection::sendTcpMessage(const char *message)
{
    send(_tcpSocket, message, strlen(message), 0);
}

void TcpConnection::_initSocket()
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
}

void TcpConnection::_ThreadFunc()
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
        _parse(buffer);
    }
}

void TcpConnection::_parse(const std::string &message)
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
            _loginRequest(ss);
        }
        start = end + 1;
    }
}

void TcpConnection::_loginRequest(std::istringstream &ss)
{
    int playerCount;
    int playerFd;

    ss >> playerCount;
    ss >> _serverFd;
    std::cout << "Server fd: " << _serverFd << std::endl;
}

void TcpConnection::_deletePlayer(int fd)
{
    std::map<int, ServerPlayer *>::iterator it = _players.find(fd);
    if (it != _players.end())
    {
        delete it->second;
        _players.erase(it);
    }
}