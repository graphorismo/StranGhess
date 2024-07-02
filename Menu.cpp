#include "Menu.hpp"
#include <algorithm>
#include <cstdint>
#include <string>

auto Menu::GetShowedOptions() -> std::vector<std::string>
{
    std::vector<std::string> showed;
    for (auto id : showedOptionsIds)
    {
        showed.emplace_back(allOptions.at(id));
    }
    return showed;
}

auto Menu::UpdateByInputingSymbol(char symbol) -> void
{
    switch (symbol) {
        case 'w':
            if(chosenOptionId == 0) break;
            chosenOptionId--;
            break;

        case 's': 
            if(chosenOptionId == showedOptionsIds.size()-1) break;
            chosenOptionId++;
            break;

        case 'f':
        {
            auto ids = optionsSwitchRules(chosenOptionId, endFlag);
            if (ids.size() > 0)
            {
                showedOptionsIds = ids;
                chosenOptionId = ids[0];
            }
            break;
        }

        default:
            break;
    }
}

auto Menu::GetChosenOption() -> std::string
{
    return allOptions.at(showedOptionsIds.at(chosenOptionId));
}

auto Menu::GetChosenOptionRelativeId() -> int8_t
{
    return std::find(showedOptionsIds.begin(), showedOptionsIds.end(), chosenOptionId) - showedOptionsIds.begin();
}

Menu::Menu(std::vector<std::string> allOptions, std::vector<int8_t> startShowedIds, std::function<std::vector<int8_t>(const int8_t, bool &)> optionsSwitchRules)
 :  allOptions(allOptions), showedOptionsIds(startShowedIds), 
    optionsSwitchRules(optionsSwitchRules), chosenOptionId(0)
{

}

auto Menu::IsChoicesPathEnded() -> bool
{
    return endFlag;
}