#pragma once

#include "BasePackage.hpp"

struct ServerShutdownPackage : public BasePackage
{
    ServerShutdownPackage();
    int pId;
    MSGPACK_DEFINE(pId, MSGPACK_BASE(BasePackage));
};