#include "Game.h"

int main()
{
   // initialize game engine
    Game game; //TODO: parameterize the game engine - stuff like window size
    sf::Clock clock;

    while (game.running()) {

        // Update
        sf::Int64 game_update_start = clock.getElapsedTime().asMilliseconds();
        game.update();
        sf::Int64 game_update_end = clock.getElapsedTime().asMilliseconds();

        // Render
        sf::Int64 game_render_start = clock.getElapsedTime().asMilliseconds();
        game.render();
        sf::Int64 game_render_end = clock.getElapsedTime().asMilliseconds();

        std::cout << "Update took " << game_update_end - game_update_start << std::endl;
        std::cout << "Render took " << game_render_end - game_render_start << std::endl;
        std::cout << "_____________________" << std::endl;
    }

    return 0;
}