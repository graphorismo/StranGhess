#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include "Menu.hpp"
#include "Desk.hpp"
#include "NcursesSystemInput.hpp"
#include "NcursesSystemOutput.hpp"

enum class GameStates
{
    UNKNOWN = 0,

    IN_MENU,
    ON_DESK,

    EXIT
};

class Game
{
public:
    Game(std::string settingsDirPath);
    bool IsEnded();
    void Run();

private:
    std::unique_ptr<Menu> mainMenu;
    Desk chessDesk;
    GameStates state = GameStates::UNKNOWN;
    SystemInterfaces sysInterfaces = 
    {
        .sysInput = std::shared_ptr<NcursesSystemInput>(new NcursesSystemInput()),
        .sysOutput = std::shared_ptr<NcursesSystemOutput>(new NcursesSystemOutput())
    };

};