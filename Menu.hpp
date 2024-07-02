#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include <utility>
#include <vector>

class Menu
{
    std::vector<std::string> allOptions;
    std::vector<int8_t> showedOptionsIds;
    int8_t chosenOptionId;
    std::function<std::vector<int8_t>(const int8_t, bool &)> optionsSwitchRules;
    bool endFlag = false;

public:
    Menu(std::vector<std::string> allOptions, std::vector<int8_t> startShowedIds, std::function<std::vector<int8_t>(const int8_t, bool &)> optionsSwitchRules);
    std::vector<std::string> GetShowedOptions();
    std::string GetChosenOption();
    int8_t GetChosenOptionRelativeId();
    void UpdateByInputingSymbol(char symbol);
    bool IsChoicesPathEnded();
};