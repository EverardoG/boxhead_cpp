#ifndef LEVELVIEW_H
#define LEVELVIEW_H

#include "GameView.h"

class LevelView : public GameView
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
        LevelView(sf::RenderWindow* _window);
        virtual ~LevelView();

        // Functions
        void update();
        void render();
};

#endif