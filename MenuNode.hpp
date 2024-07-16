#pragma once

#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class MenuNode
{
public:
    MenuNode(std::string name);

    std::string GetName();
    std::string GetChosenOption();
    std::shared_ptr<MenuNode> GetChosenMenuNode();
    std::vector<std::string> GetOptions();
    void ChooseOption(std::string option);

    void AddOption(std::string optionName, std::shared_ptr<MenuNode> linkedNode, std::function<void()> action);

private:
    std::string name;
    std::vector<std::string> options;
    std::vector<std::function<void()>> actions;
    int chosenOptionId = 0;
    std::vector<std::shared_ptr<MenuNode>> nodes;
};