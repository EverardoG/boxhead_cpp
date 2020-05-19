#include "Game.h"

int main()
{
   // initialize game engine
    Game game; //TODO: parameterize the game engine - stuff like window size
    sf::Clock clock;

    while (game.running()) {
        sf::Int64 start_time_ms = clock.getElapsedTime().asMilliseconds();

        // Update
        sf::Int64 game_start_time_ms = clock.getElapsedTime().asMilliseconds();
        game.update();
        sf::Int64 game_end_time_ms = clock.getElapsedTime().asMilliseconds();

        // Render
        sf::Int64 game_render_start_time_ms = clock.getElapsedTime().asMilliseconds();
        game.render();
        sf::Int64 game_render_end_time_ms = clock.getElapsedTime().asMilliseconds();

        sf::Int64 end_time_ms = clock.getElapsedTime().asMilliseconds();
        // std::cout << "Main loop took " << end_time_ms-start_time_ms << std::endl;
        // std::cout << "Game update took " << game_end_time_ms - game_start_time_ms << std::endl;
        // std::cout << "Game render took " << game_render_end_time_ms - game_render_start_time_ms << std::endl;
        // std::cout << "__________________________" << std::endl;
    }

    return 0;
}