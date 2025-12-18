#include <iostream>
#include "Game.h"

int main()
{
    // Init Game engine
    Game game;

    // Game loop
    while (game.Running())
    {
        // Update (frame)
        game.Update();

        // Render
        game.Render();

    }
    
    // End of application

    return 0;
}