#include "BasePacket.hpp"

class NewBasicNpcPackage : public BasePacket
{
public:
    NewBasicNpcPackage();
    NewBasicNpcPackage(int id, float x, float y, float targetX, float targetY, float speed, float health, int type);
    int id;
    float x; 
    float y;
    int type;
    float targetX;
    float targetY;
    float speed;
    float health;
    MSGPACK_DEFINE(id, x, y, targetX, targetY, speed, health, type);
};