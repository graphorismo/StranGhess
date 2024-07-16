#include "Game.hpp"
#include "Menu.hpp"
#include "MenuNode.hpp"
#include <algorithm>
#include <memory>

Game::Game(std::string dirPath)
:   state(GameStates::IN_MENU), 
    mainMenu(std::unique_ptr<Menu>(nullptr))
{
    auto mainScreen = std::shared_ptr<MenuNode>(new MenuNode("Main Screen"));
    auto gameTypeScreen = std::shared_ptr<MenuNode>(new MenuNode("Game Type Screen"));

    mainScreen->AddOption("START", gameTypeScreen, [](){} );
    mainScreen->AddOption("EXIT", mainScreen, [&](){state = GameStates::EXIT;});

    gameTypeScreen->AddOption("CLASSIC", gameTypeScreen, [&](){state = GameStates::ON_DESK;});
    gameTypeScreen->AddOption("BACK", mainScreen, [](){} );

    auto menu = std::unique_ptr<Menu>(new Menu({mainScreen, gameTypeScreen}));
    mainMenu = std::move(menu);

    Desk::FileParser fileParser(dirPath);
    chessDesk = fileParser.LoadDesk();


}

void Game::Run()
{
    switch (state) 
    {
        case GameStates::IN_MENU:
        {
            auto showedOptions = mainMenu->GetShowedOptions();
            auto idOfChosen = std::find(showedOptions.begin(), 
                                        showedOptions.end(), mainMenu->GetChosenOption()) - showedOptions.begin();
            sysInterfaces.sysOutput->DrawMenu(showedOptions, idOfChosen);

            auto symbol = sysInterfaces.sysInput->GetPressedSymbol();
            mainMenu->UpdateByInputingSymbol(symbol);

            break;
        }

        case GameStates::ON_DESK:
        {
            auto placement = chessDesk.GetPlacement();
            sysInterfaces.sysOutput->DrawDesk(placement);

            auto symbol = sysInterfaces.sysInput->GetPressedSymbol();
            chessDesk.UpdateByInputingSymbol(symbol);

            break;
        }

        case GameStates::UNKNOWN:
        default:
            break;
    }
}

bool Game::IsEnded()
{
    return state == GameStates::EXIT;
}