#pragma once

#include "ServerPackages.hpp"
#include <msgpack.hpp>

struct BasePackage {
    int packageId;

    BasePackage();

    BasePackage(ServerPackage packageId);

    MSGPACK_DEFINE(packageId);
};