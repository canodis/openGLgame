#pragma once

enum ServerPackage
{
    // Udp packages
    PositionRequest = 0,
    Ping = 1,
    ServerShutDown = 2,
    BasicNpcRequest = 3,
    ThrowObject = 7,

    // Tcp packages
    NewPlayer = 4,
    PlayerLeft = 5,
    PlayerLogin = 6,
    NewPlayers = 7,
};