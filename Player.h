/*
    Class for encapsulating the player object
 */

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
    private:
        // Variables

        // Functions


    public:
        // Constructors and Destructors
        Player();
        virtual ~Player();

        // Functions
        void initVariables();
        // void updateVel();
        // void updatePos();
        void update(float new_x_vel, float new_y_vel);

        // Variables
        sf::RectangleShape render;
        float x_pos;
        float y_pos;
        float x_vel;
        float y_vel;
};

#endif