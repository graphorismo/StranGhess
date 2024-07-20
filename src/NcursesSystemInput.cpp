#include "NcursesSystemInput.hpp"

#include <ncurses.h>

char16_t NcursesSystemInput::GetPressedSymbol()
{
    auto ch = getch();
    return ch;
}