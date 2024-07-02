#include "NcursesSystemOutput.hpp"

#include "ncurses.h"
#include <string>

NcursesSystemOutput::NcursesSystemOutput()
{
    initscr();
}

NcursesSystemOutput::~NcursesSystemOutput()
{
    endwin();
}

auto NcursesSystemOutput::DrawDesk(std::vector<std::vector<std::int8_t>> placement) -> void
{

}

auto NcursesSystemOutput::DrawMenu(std::vector<std::string> menuOptions, std::uint8_t chosenOption) -> void
{
    for (auto i = 0; i < menuOptions.size(); i++) 
    {
        if(i == chosenOption) mvprintw(i, 0, "%s", std::string("> "+menuOptions[i]).data());
        else mvprintw(i, 0, "%s", std::string("  "+menuOptions[i]).data());
    }
    refresh();
}