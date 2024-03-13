#pragma once

enum ServerPackage
{

    #pragma region Udp packages

    PositionRequest = 0,
    Ping = 1,
    ServerShutDown = 2,
    BasicNpcPosition = 3,
    NewBasicNpc = 40,

    #pragma endregion

    #pragma region Tcp packages

    NewPlayer = 4,
    PlayerLeft = 5,
    PlayerLogin = 6,
    NewPlayers = 7,

    //turret
    NewTurret = 20,
    TurretAttack = 21,
    TurretBulletHit = 22,
    TurretBulletDestroy = 23,
    NpcDie = 24,


    #pragma endregion
};