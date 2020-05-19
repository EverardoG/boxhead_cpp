#ifndef LEVELVIEW_H
#define LEVELVIEW_H

#include "GameView.h"
#include "CollisionEngine.h"

class LevelView : public GameView
{
    private:
        Player* player;
        std::vector<Zombie*> zombie_vec;
        std::vector<Bullet*> bullet_vec;
        sf::Int32 weapon_loop_time = sf::milliseconds(333).asMilliseconds();
        sf::Int32 last_weapon_time = sf::milliseconds(0).asMilliseconds();
        CollisionEngine* collisionEngine = new CollisionEngine();

        // Functions
        void initVariables();
        void checkCollisions();
        void spawnZombie(int zid);
        float getDistBtnChars(Character* char1, Character* char2);
        bool zombieBulletCollision(Zombie* zombie, Bullet* bullet);

    public:
        // Constructors and Destructors
        LevelView(sf::RenderWindow* _window);
        virtual ~LevelView();

        // Functions
        void update();
        void render();
};

#endif