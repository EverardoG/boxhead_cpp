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
        Zombie(int zid);
        void goTowards(float x_des, float y_des);
        int id;
        bool colliding_with_zombie;


};

#endif