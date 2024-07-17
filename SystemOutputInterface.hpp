#pragma once

#include "Vector2d.hpp"
#include <cstdint>
#include <string>
#include <vector>


class SystemOutputInterface
{
public:
   virtual void DrawDesk(std::vector<std::vector<std::int8_t>> placement, Vector2d<int8_t> cursor) = 0;
   virtual void DrawMenu(std::vector<std::string> menuOptions, std::uint8_t chosenOption) = 0;
};