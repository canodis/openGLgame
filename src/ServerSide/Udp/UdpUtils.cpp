#include "UdpConnection.hpp"

ServerPlayer *UdpConnection::_createPlayer(int fd, int x, int y)
{
    ServerPlayer *player = new ServerPlayer(fd, x, y);
    _players.insert(std::pair<int, ServerPlayer *>(fd, player));
    return player;
}
