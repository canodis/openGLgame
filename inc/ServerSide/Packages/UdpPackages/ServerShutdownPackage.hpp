#pragma once

#include "Package.hpp"

struct ServerShutdownPackage
{
    int packageId;
    ServerShutdownPackage();
    MSGPACK_DEFINE(packageId);
};