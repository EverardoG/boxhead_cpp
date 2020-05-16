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
        sf::Clock clock;
        sf::Int32 loop_time = sf::milliseconds(16).asMilliseconds();
        sf::Int32 last_update_time = sf::milliseconds(0).asMilliseconds();

        sf::Event ev;
        std::chrono::_V2::high_resolution_clock::time_point timelastwasd;
        Player* player;
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

        sf::Int32 weapon_loop_time = sf::milliseconds(333).asMilliseconds();
        sf::Int32 last_weapon_time = sf::milliseconds(0).asMilliseconds();

        // Functions
        void initVariables();
        void initWindow();
        void checkCollisions();
        void spawnZombie(int zid);
        float getDistBtnChars(Character* char1, Character* char2);

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