#include "Game.h"

int main()
{
   // initialize game engine
   Game game; //TODO: parameterize the game engine - stuff like window size

    // std::cout << game.zombie.x_pos << " | " << game.zombie.y_pos << std::endl;
    // Game Loop
    // bool time_check = true;
    while (game.running()) {

        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        //     std::cout << "I FEEL IT" << std::endl;
        // }
        // if (time_check == true) {
        //     std::cout << "0  " << std::endl;
        //     time_check = false;
        // }
        // else {
        //     std::cout << "1  " << std::endl;
        //     time_check = true;
        // }

        // Update
        game.update();
        // std::cout << "hello?" << std::endl;

        // Render
        game.render();
        // std::cout << "rendering" << std::endl;
    }

    // std::cout << "hello again!";
    return 0;
}