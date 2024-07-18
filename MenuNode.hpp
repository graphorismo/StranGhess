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
    std::string GetSelectedOption();
    std::shared_ptr<MenuNode> GetChosenMenuNode();
    std::vector<std::string> GetOptions();
    void SelectOption(std::string option);
    void ChooseSelectedOption();

    void AddOption(std::string optionName, std::shared_ptr<MenuNode> linkedNode, std::function<void()> action);

private:
    std::string name;
    std::vector<std::string> options;
    int selectedOptionId = 0;
    std::vector<std::function<void()>> actions;
    std::vector<std::shared_ptr<MenuNode>> nodes;
};