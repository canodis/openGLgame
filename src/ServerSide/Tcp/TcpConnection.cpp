#include "TcpConnection.hpp"

TcpConnection::TcpConnection(std::map<int, ServerPlayer *> &players, int &serverFd) : _players(players), _serverFd(serverFd)
{
    _buffer = "";
    _accumulatedTime = 0;
    _tcpSocket = -1;
    _initResponseHandlers();
    _connectionHandleThread = std::thread(&TcpConnection::_tcpConnectionController, this);
    _connectionHandleThread.detach();
}

void TcpConnection::_tcpConnectionController()
{
    while (true)
    {
        if (_connectSocket() == false)
        {
            sleep(2);
            continue;
        }
        _tcpThread = std::thread(&TcpConnection::_listen, this);
        Client::getInstance().udpConnection->connect();
        _tcpThread.join();
        Client::getInstance().udpConnection->disconnect();
        std::cout << "Reconnecting to server..." << std::endl;
    }
}

TcpConnection::~TcpConnection()
{
    close(_tcpSocket);
}

void TcpConnection::sendTcpMessage(const char *message)
{
    send(_tcpSocket, message, strlen(message), 0);
}

bool TcpConnection::_connectSocket()
{
    if (_tcpSocket != -1)
        close(_tcpSocket);
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
        return false;
    }
    sendTcpMessage(GUARD);

    return true;
}

void TcpConnection::_listen()
{
    char buffer[1024];
    while (true)
    {
        memset(buffer, 0, sizeof(buffer));
        if (recv(_tcpSocket, buffer, sizeof(buffer), 0) <= 0)
        {
            std::cout << "Server closed." << std::endl;
            break;
        }
        _handleResponse(buffer);
    }
}

static int intLen(int number)
{
    int len = 0;
    while (number > 0)
    {
        number /= 10;
        len++;
    }
    return len;
}

void TcpConnection::_handleResponse(const std::string &message)
{
    _buffer = message;

    bool done = false;
    while (!done && !_buffer.empty())
    {
        if (_buffer.length() < 2)
        {
            done = true;
            break;
        }

        std::istringstream iss(_buffer);
        int messageLength;
        iss >> messageLength;

        if (_buffer.size() < messageLength)
        {
            done = true;
            break;
        }

        int command;
        iss >> command;

        // +2 for the space
        std::string::iterator _bufferIterator = _buffer.begin();
        std::string messageContent(_bufferIterator + intLen(messageLength) + intLen(command) + 2, _bufferIterator + intLen(messageLength) + messageLength);

        std::istringstream messageStream(messageContent);
        if (_tcpPackageHandlers.find(command) != _tcpPackageHandlers.end())
        {
            _tcpPackageHandlers[command](messageStream);
        }

        _buffer.erase(0, messageLength + intLen(messageLength));

        if (_buffer.empty())
        {
            done = true;
        }
    }
}

// std::istringstream iss(message);
// int messageLength;
// int command;
// std::cout << "Received message: " << message << std::endl;
// iss >> messageLength;
// iss >> command;
// std::lock_guard<std::mutex> lock(Client::getInstance()._playerMutex);
// if (_tcpPackageHandlers.find(command) != _tcpPackageHandlers.end())
// {
//     _tcpPackageHandlers[command](iss);
// }

void TcpConnection::sendPlayerNew(Player *player)
{
    std::string message = std::to_string((int)ServerPackage::NewPlayer) + " " + std::to_string(_serverFd) + " " + std::to_string(player->GetPosition().x) + " " + std::to_string(player->GetPosition().y) + " " + std::to_string(player->GetTargetPosition().x) + " " + std::to_string(player->GetTargetPosition().y);
    std::cout << "Sending new player message: " << message << std::endl;
    sendTcpMessage(message.c_str());
}