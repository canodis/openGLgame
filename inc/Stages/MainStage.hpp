#pragma once

#include "Navigator.hpp"
#include "Game.hpp"
#include "NpcController.hpp"
#include <ft2build.h>
#include "TurretNpc.hpp"
#include FT_FREETYPE_H
#include "Stage.hpp"

class MainStage : public Stage
{
public:
    MainStage();
    void initStage() override;
    void runStage() override;
    void endStage() override;
    ~MainStage();
private:
    MapController mapController;
    Player *player;
    Scene *scene;
    Camera2D *camera;
    NpcController *npcController;
    void terminateThreads();
};