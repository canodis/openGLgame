#include "Navigator.hpp"
#include "MainStage.hpp"

void Test();

int main(int ac, char **av)
{
    Navigator &navigator = Navigator::getInstance();
    Stage *mainScene = new MainStage();

    navigator.setActiveStage(mainScene);
    while (navigator.isRunning)
    {
        navigator.runActiveStage();
    }

    // TEST //
    //  Test();
}

#include "PlayerPositionPackage.hpp"

void Test()
{
    PlayerPositionPackage playerPositionPackage(5, 0.0f, 0.0f, 0.0f, 0.0f);
    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, playerPositionPackage);

    std::string rawData(sbuf.data(), sbuf.size());
    msgpack::object_handle oh = msgpack::unpack(rawData.data(), rawData.size());
    msgpack::object deserialized = oh.get();
    BasePacket basePacket;
    deserialized.convert(basePacket);
}
