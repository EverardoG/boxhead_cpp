#ifndef BULLET_H
#define BULLET_H

#include "dependencies.h"

class Bullet
{
    protected:
        sf::RectangleShape m_render;

    public:
        Bullet(float startx, float starty, float angle);
        ~Bullet();

        void update();

        sf::RectangleShape getRender();

        float start_x;
        float start_y;

        float curr_x;
        float curr_y;

        float end_x;
        float end_y;

        float speed = 30.f;

        float current_distance = 0.f;
        float final_distance = 100.f;

        bool finished = false;

        // int direction_x; // left is -1, nuetral 0, right is 1
        // int direction_y; // down is 1, nuetral 0, up is -1
};

#endif