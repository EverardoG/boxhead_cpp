/*
    Class for encapsulating game and objects inside it, along with updates and renders
 */

#ifndef GAME_H
#define GAME_H

#include "dependencies.h"
#include "Player.h"
#include "Zombie.h"
#include "Bullet.h"
#include "GameView.h"
#include "MenuView.h"
#include "LevelView.h"

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

        GameView* game_view;

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
};

#endif