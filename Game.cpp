#include "Game.hpp"

Game::Game(std::string dirPath)
:state(GameStates::IN_MENU)
{
    Desk::FileParser fileParser(dirPath);
    chessDesk = fileParser.LoadDesk();

}

void Game::Run()
{
    switch (state) 
    {
        case GameStates::IN_MENU:
        {
            auto showedOptions = mainMenu.GetShowedOptions();
            auto idOfChosen = mainMenu.GetChosenOptionRelativeId();
            sysInterfaces.sysOutput->DrawMenu(showedOptions, idOfChosen);

            auto symbol = sysInterfaces.sysInput->GetPressedSymbol();
            mainMenu.UpdateByInputingSymbol(symbol);

            if(!mainMenu.IsChoicesPathEnded()) break;
            auto option = mainMenu.GetChosenOption();
            if (option == "EXIT") {
                state = GameStates::EXIT;
            }
            else if (option == "CLASSIC") {
                state = GameStates::ON_DESK;
            }
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