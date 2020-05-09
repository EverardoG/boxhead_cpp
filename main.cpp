#include <iostream>
#include "Game.h"

int main()
{
   // initialize game engine
   Game game; //TODO: parameterize the game engine - stuff like window size

    // Game Loop
    while (game.running()) {
        // Update
        game.update();

        // Render
        game.render();
        // std::cout << "rendering" << std::endl;
    }

    // std::cout << "hello again!";
    return 0;
}