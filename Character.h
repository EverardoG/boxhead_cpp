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
        const float width = 10.f;
        const float height = 15.f;
        sf::RectangleShape render; // this is called shape in the tutorials
        sf::Vector2f pos; // position
        float max_speed = 1.f;

    public:
        // Constructors and Destructors
        Character(sf::Vector2f spawn_pos, sf::Color fill_color = sf::Color::White, sf::Color outline_color = sf::Color::Black, float outline_thickness = 3.f);
        virtual ~Character();

        // Functions
        void setDesVel(sf::Vector2f new_des_vel);
        void setActVel(sf::Vector2f new_act_vel);
        void update();
        void render();

        // Variables
        sf::Vector2i dir = sf::Vector2i(1,1); // direction
        sf::Vector2f des_vel = sf::Vector2f(0.f,0.f); // desired velocity
        sf::Vector2f act_vel = sf::Vector2f(0.f,0.f); // actual velocity (taking into account collisions)

        float angle = 0.f;

        bool is_attacking = false;
        bool in_collision = false;

};

#endif