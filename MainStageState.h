#ifndef MAINSTAGESTATE_H
#define MAINSTAGESTATE_H

#include "GameState.h"

class MainStageState : public GameState
{
    private:
        Player* player;
        std::vector<Zombie*> zombie_vec;
        std::vector<Bullet*> bullet_vec;
        sf::Int32 weapon_loop_time = sf::milliseconds(333).asMilliseconds();
        sf::Int32 last_weapon_time = sf::milliseconds(0).asMilliseconds();

        // Functions
        void initVariables();
        void checkCollisions();
        void spawnZombie(int zid);
        float getDistBtnChars(Character* char1, Character* char2);

    public:
        // Constructors and Destructors
        MainStageState(sf::RenderWindow* _window);
        virtual ~MainStageState();

        // Functions
        std::string update(std::unordered_map<std::string, bool> _input_map);
        void render();

        // states you can get to from this state
        std::unordered_map<std::string, GameState*> adjStates;
};

#endif