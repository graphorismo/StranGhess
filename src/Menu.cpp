#include "Menu.hpp"
#include <algorithm>
#include <cstdint>
#include <string>

std::vector<std::string> Menu::GetShowedOptions()
{
    return currentNode->GetOptions();
}

void Menu::UpdateByInputingSymbol(char symbol)
{
    auto allOptions = currentNode->GetOptions();
    auto selectedOption = currentNode->GetSelectedOption();
    auto optionIter = std::find(allOptions.begin(), allOptions.end(), selectedOption);

    if (optionIter == allOptions.end()) currentNode = nodes.at(0);

    switch (symbol) {
        case 'w':
            if(optionIter == allOptions.begin()) break;
            optionIter--;
            currentNode->SelectOption(*optionIter);
            break;

        case 's': 
            if(optionIter == (allOptions.end()--)) break;
            optionIter++;
            currentNode->SelectOption(*optionIter);
            break;

        case 'f':
        {
            currentNode->ChooseSelectedOption();
            currentNode = currentNode->GetChosenMenuNode();
        }

        default:
            break;
    }
}

std::string Menu::GetSelectedOption()
{
    return currentNode->GetSelectedOption();
}

Menu::Menu(std::vector<std::shared_ptr<MenuNode>> nodes)
:   nodes(nodes), 
    currentNode(nodes.at(0))
{

}
