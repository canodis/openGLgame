#include "Navigator.hpp"
#include "LoginStage.hpp"
#include "MainStage.hpp"


int main(int ac, char **av)
{
    Scene::getInstance();
    Navigator &navigator = Navigator::getInstance();
    Stage *loginScene = new LoginStage();

    navigator.setActiveStage(loginScene);
    while (navigator.isRunning)
    {
        navigator.runActiveStage();
    }
}
