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

std::string MenuNode::GetChosenOption()
{
    return options[chosenOptionId];
}

std::vector<std::string> MenuNode::GetOptions()
{
    return options;
}

std::shared_ptr<MenuNode> MenuNode::GetChosenMenuNode()
{
    return nodes[chosenOptionId];
}

void MenuNode::ChooseOption(std::string option)
{
    auto findResult = std::find(options.begin(), options.end(), option);
    if(findResult != options.end())
    {
        chosenOptionId = findResult - options.begin();
        actions[chosenOptionId]();
    }
}

void MenuNode::AddOption(std::string optionName, std::shared_ptr<MenuNode> linkedNode, std::function<void()> action)
{
    options.push_back(optionName);
    nodes.push_back(linkedNode);
    actions.push_back(action);
}