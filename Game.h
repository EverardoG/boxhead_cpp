/*
    Class for encapsulating game and objects inside it, along with updates and renders
 */

#ifndef GAME_H
#define GAME_H

#include "dependencies.h"
#include "Player.h"
#include "Zombie.h"
#include "Bullet.h"

class Game
{
    private:
        //Variables
        sf::RenderWindow* window = nullptr; // want to be able to delete this so we want to dynamically allocate it
        sf::VideoMode videomode;
        sf::Event ev;
        // std::chrono::_V2::high_resolution_clock::time_point timelastpolled;
        std::chrono::_V2::high_resolution_clock::time_point timelastwasd;
        Player player;
        std::vector<Zombie*> zombie_vec;
        std::vector<Bullet*> bullet_vec;
        bool last_event_was_key_released = false;
        std::chrono::_V2::high_resolution_clock::time_point timelast_W;
        std::chrono::_V2::high_resolution_clock::time_point timelast_A;
        std::chrono::_V2::high_resolution_clock::time_point timelast_S;
        std::chrono::_V2::high_resolution_clock::time_point timelast_D;
        // bool timelast_A;
        // bool lastS_released = false;
        // bool lastW_released = false;
        int64_t silly_count = 0;

        // Functions
        void initVariables();
        void initWindow();
        void checkCollisions();

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
};

#endif