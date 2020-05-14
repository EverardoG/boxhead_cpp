#include "Game.h"

int main()
{
   // initialize game engine
    Game game; //TODO: parameterize the game engine - stuff like window size

    while (game.running()) {
        // Update
        game.update();

        // Render
        game.render();
    }

    return 0;
}