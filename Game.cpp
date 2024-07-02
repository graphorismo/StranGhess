#include "Game.hpp"

Game::Game(std::string dirPath)
:state(GameStates::IN_MENU)
{

}

auto Game::Run() -> void
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
            break;

        case GameStates::UNKNOWN:
        default:
            break;
    }
}

auto Game::IsEnded() -> bool
{
    return state == GameStates::EXIT;
}