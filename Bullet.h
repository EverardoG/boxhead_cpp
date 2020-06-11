#ifndef BULLET_H
#define BULLET_H

#include "dependencies.h"
#include "InGameObject.h"

class Bullet : public InGameObject
{
    protected:
        float speed = 30.f;

    public:
        Bullet(sf::Vector2f _start_pos, float _angle);
        ~Bullet();

        void update();

        float angle;
        sf::Vector2f start_pos;
        sf::Vector2f cur_pos;

        float current_distance = 0.f;
        float final_distance = 100.f;

        bool finished = false;
};

#endif