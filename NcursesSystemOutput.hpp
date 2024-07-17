#pragma once

#include "SystemInterfaces.hpp"
#include "Vector2d.hpp"

class NcursesSystemOutput : public SystemOutputInterface
{
public:
    NcursesSystemOutput();
    ~NcursesSystemOutput();

    void DrawDesk(std::vector<std::vector<char>> placement, Vector2d<int8_t> cursor) override;
    void DrawMenu(std::vector<std::string> menuOptions, std::uint8_t chosenOption) override;
};