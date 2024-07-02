#pragma once

#include "SystemInterfaces.hpp"

class NcursesSystemOutput : public SystemOutputInterface
{
public:
    NcursesSystemOutput();
    ~NcursesSystemOutput();

    void DrawDesk(std::vector<std::vector<std::int8_t>> placement) override;
    void DrawMenu(std::vector<std::string> menuOptions, std::uint8_t chosenOption) override;
};