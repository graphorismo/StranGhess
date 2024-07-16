#pragma once

#include "MenuNode.hpp"
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Menu
{
public:
    Menu(std::vector<std::shared_ptr<MenuNode>> nodes);
    std::vector<std::string> GetShowedOptions();
    std::string GetChosenOption();
    void UpdateByInputingSymbol(char symbol);
    bool IsChoicesPathEnded();

private:
    
    std::vector<std::shared_ptr<MenuNode>> nodes;
    std::shared_ptr<MenuNode> currentNode;
};