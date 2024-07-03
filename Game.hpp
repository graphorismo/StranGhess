#pragma once

#include <cstdint>
#include <string>
#include <memory>

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
    explicit Game(std::string settingsDirPath);
    bool IsEnded();
    void Run();

private:
    Menu mainMenu = Menu(
        {"START", "EXIT", "CLASSIC", "BACK"},
        { 0 , 1 },
        [](const int8_t id, bool & endFlag) -> std::vector<int8_t>
        {
            switch (id) 
            {
                case 0://start
                    return {2, 3};
                
                case 1://exit
                    endFlag = true;
                    return {};

                case 2://classic
                    endFlag = true;
                    return {0, 1};
                
                case 3://back
                    return {};

                default:
                    return {};
            }
        }
    );
    Desk chessDesk;
    GameStates state = GameStates::UNKNOWN;
    SystemInterfaces sysInterfaces = 
    {
        .sysInput = std::shared_ptr<NcursesSystemInput>(new NcursesSystemInput()),
        .sysOutput = std::shared_ptr<NcursesSystemOutput>(new NcursesSystemOutput())
    };

};