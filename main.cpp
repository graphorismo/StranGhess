#include <exception>
#include <ncurses.h>
#include <iostream>

#include "Game.hpp"



void mainThread()
{

}

int main ()
{
    try {
        Game game("./figures");
        while (game.IsEnded() == false)
        {
            game.Run();
        }
    } 
    catch (const std::exception& exc) 
    {
        std::cout<<exc.what();
    }
}