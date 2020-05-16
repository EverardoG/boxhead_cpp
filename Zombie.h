/*
    Class for encapsulating the player object
 */

#ifndef ZOMBIE_H
#define ZOMBIE_H

#include"dependencies.h"
#include"Character.h"

class Zombie: public Character
{
    public:
        Zombie(int zid, sf::Vector2f spawn_pos);
        void goTowards(float x_des, float y_des);
        int id;
        float dist_from_player;
};

#endif