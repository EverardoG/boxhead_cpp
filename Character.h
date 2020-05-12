/*
    Class for encapsulating the abstract character class
    This class is inherited by the zombie and player classes
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include"dependencies.h"

class Character
{
    protected:
        // Variables
        float x_vel;
        float y_vel;

        // static const sf::Color outline_color;
        // float outline_thickness;

    public:
        // Constructors and Destructors
        // sf::Color fill_color = ;

        Character(sf::Color fill_color = sf::Color::White, sf::Color outline_color = sf::Color::Black, float outline_thickness = 3.f);
        virtual ~Character();

        // Functions
        void initVariables();
        void updateVel(float new_x_vel, float new_y_vel);
        void update();
        // void set_color();

        // virtual void set_color();

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