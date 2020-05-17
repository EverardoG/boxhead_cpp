/*
    Class for encapsulating game and objects inside it, along with updates and renders
 */

#ifndef GAME_H
#define GAME_H

#include "dependencies.h"
#include "Player.h"
#include "Zombie.h"
#include "Bullet.h"
#include "GameState.h"
#include "MainStageState.h"
#include "MainMenuState.h"

class Game
{
    private:
        //Variables
        sf::VideoMode videomode;
        sf::Clock clock;
        sf::Int32 loop_time = sf::milliseconds(16).asMilliseconds();
        sf::Int32 last_update_time = sf::milliseconds(0).asMilliseconds();
        int64_t loop_count = 0;
        sf::Event ev;
        std::vector<std::string> all_inputs = { "W", "A", "S", "D", "SPACE" };

        GameState* game_state;

        void initVariables();
        void initWindow();

    public:
        // Constructors and Destructors
        Game();
        virtual ~Game();

        // Functions
        void pollInputs();
        void update();
        void render();

        //Accessors
        const bool running() const;

        sf::RenderWindow* window = nullptr; // want to be able to delete this so we want to dynamically allocate it
        std::unordered_map<std::string, bool> input_map; // key is the input, value is True if that input is being pressed/used
};

#endif