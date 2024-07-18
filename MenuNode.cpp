#include "MenuNode.hpp"

#include <algorithm>
#include <memory>
#include <tuple>

MenuNode::MenuNode(std::string name)
: name(name)
{

}

std::string MenuNode::GetName()
{
    return name;
}

std::string MenuNode::GetSelectedOption()
{
    return options[selectedOptionId];
}

std::vector<std::string> MenuNode::GetOptions()
{
    return options;
}

std::shared_ptr<MenuNode> MenuNode::GetChosenMenuNode()
{
    return nodes[selectedOptionId];
}

void MenuNode::SelectOption(std::string option)
{
    auto findResult = std::find(options.begin(), options.end(), option);
    if ( findResult == options.end()) return;
    selectedOptionId = findResult - options.begin();
}

void MenuNode::ChooseSelectedOption()
{
    actions[selectedOptionId]();
}

void MenuNode::AddOption(std::string optionName, std::shared_ptr<MenuNode> linkedNode, std::function<void()> action)
{
    options.push_back(optionName);
    nodes.push_back(linkedNode);
    actions.push_back(action);
}