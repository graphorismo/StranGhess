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

void NcursesSystemOutput::DrawDesk(std::vector<std::vector<std::int8_t>> placement)
{

}

void NcursesSystemOutput::DrawMenu(std::vector<std::string> menuOptions, std::uint8_t chosenOption)
{
    for (auto i = 0; i < menuOptions.size(); i++) 
    {
        if(i == chosenOption) mvprintw(i, 0, "%s", std::string("> "+menuOptions[i]).data());
        else mvprintw(i, 0, "%s", std::string("  "+menuOptions[i]).data());
    }
    refresh();
}