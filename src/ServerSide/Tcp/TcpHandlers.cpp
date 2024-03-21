#include "TcpConnection.hpp"
#include "ServerPackages.hpp"
#include "Colors.hpp"

void TcpConnection::_initResponseHandlers()
{
    _tcpPackageHandlers[(int)ServerPackage::NewPlayer] = std::bind(&TcpConnection::_newPlayerHandle, this, std::placeholders::_1);
    _tcpPackageHandlers[(int)ServerPackage::PlayerLeft] = std::bind(&TcpConnection::_playerLeftHandle, this, std::placeholders::_1);
    _tcpPackageHandlers[(int)ServerPackage::PlayerLogin] = std::bind(&TcpConnection::_playerLoginHandle, this, std::placeholders::_1);
    _tcpPackageHandlers[(int)ServerPackage::NewTurret] = std::bind(&TcpConnection::_handleNewTurret, this, std::placeholders::_1);
    _tcpPackageHandlers[(int)ServerPackage::TurretAttack] = std::bind(&TcpConnection::_handleTurretShoot, this, std::placeholders::_1);
    _tcpPackageHandlers[(int)ServerPackage::TurretBulletDestroy] = std::bind(&TcpConnection::_handleTurretDestroy, this, std::placeholders::_1);
    _tcpPackageHandlers[(int)ServerPackage::TurretBulletHit] = std::bind(&TcpConnection::_handleTurretHit, this, std::placeholders::_1);
    _tcpPackageHandlers[(int)ServerPackage::NpcDie] = std::bind(&TcpConnection::_npcDie, this, std::placeholders::_1);
}

void TcpConnection::_newPlayerHandle(std::istringstream &ss)
{
    int new_fd;
    float posX, posY;
    float targetX, targetY;
    ss >> new_fd >> posX >> posY >> targetX >> targetY;
    if (_players.find(new_fd) != _players.end())
    {
        _players[new_fd]->SetTargetPosition(posX, posY, targetX, targetY);
    }
    else
    {
        _players.insert(std::pair<int, ServerPlayer *>(new_fd, new ServerPlayer(new_fd, posX, posY, targetX, targetY)));        
    }
    
}

void TcpConnection::_playerLoginHandle(std::istringstream &ss)
{
    int playerCount;
    int playerFd;

    ss >> playerCount;
    ss >> _serverFd;
    std::cout << Color(Color::YELLOW) << "--------------------------------"
    << "\nPlayer Logined : PlayerFd : " << _serverFd << "\n Player count : " << playerCount << std::endl;
    for (int i = 0; i < playerCount - 1; i++)
    {
        float x, y;
        ss >> playerFd >> x >> y;
        std::cout << "Other player : " << playerFd << " " << x << " " << y << std::endl;
        _players.insert(std::pair<int, ServerPlayer *>(playerFd, new ServerPlayer(playerFd, x, y)));
    }
    std::cout << "--------------------------------" << Color(Color::RESET) << std::endl;
    Player *player = Scene::getInstance().player;
    Client::getInstance().udpConnection->sendPlayerAllData(player->GetTransform(), 
        5, 31);
    Client::getInstance().tcpConnection->sendPlayerNew(*player);
}

void TcpConnection::_playerLeftHandle(std::istringstream &ss)
{
    int fd;
    ss >> fd;
    std::map<int, ServerPlayer *>::iterator it = _players.find(fd);
    if (it != _players.end())
    {
        delete it->second;
        _players.erase(it);
    }
}