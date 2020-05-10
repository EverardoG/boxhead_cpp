/*
    Class for encapsulating the player object
 */

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#ifndef ZOMBIE_H
#define ZOMBIE_H

class Zombie
{
    private:
        // Variables
        float x_vel;
        float y_vel;

    public:
        // Constructors and Destructors

        Zombie();
        virtual ~Zombie();

        // Functions
        void initVariables();
        void updateVel(float new_x_vel, float new_y_vel);
        void update();

        // Variables
        sf::RectangleShape render;
        bool is_attacking;
        float x_pos;
        float y_pos;

        int direction_x;  // left is -1, right is 1
        int direction_y; // down is 1, up is -1

        float width = 25.f;
        float height = 50.f;

        float angle;

};

#endif