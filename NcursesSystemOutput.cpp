#include "NcursesSystemOutput.hpp"

#include "Vector2d.hpp"
#include "ncurses.h"
#include <cstddef>
#include <cstdint>
#include <string>
#include <valarray>

NcursesSystemOutput::NcursesSystemOutput()
{
    initscr();
}

NcursesSystemOutput::~NcursesSystemOutput()
{
    endwin();
}

void NcursesSystemOutput::DrawDesk(std::vector<std::vector<std::int8_t>> placement, Vector2d<int8_t> cursor)
{
    clear();
    for (size_t i = 0; i < placement.size(); ++i)
    {
        auto line = placement[i];
        for (size_t j = 0; j < line.size(); ++j)
        {
            if(Vector2d<int8_t>{static_cast<signed char>(j), static_cast<signed char>(i)} == cursor)
            {
                mvprintw(i*2, j*3, "%s", std::string("%").data());
            }
            else mvprintw(i*2, j*3, "%s", std::to_string(placement[i][j]).data());
        }
    }
    refresh();
}

void NcursesSystemOutput::DrawMenu(std::vector<std::string> menuOptions, std::uint8_t chosenOption)
{
    clear();
    for (size_t i = 0; i < menuOptions.size(); i++) 
    {
        if(i == chosenOption) mvprintw(i, 0, "%s", std::string("> "+menuOptions[i]).data());
        else mvprintw(i, 0, "%s", std::string("  "+menuOptions[i]).data());
    }
    refresh();
}