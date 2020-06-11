/*
    Class for encapsulating the abstract character class
    This class is inherited by the zombie and player classes
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include"dependencies.h"
#include "InGameObject.h"

class Character : public InGameObject
{
    protected:
        float max_speed = 1.f;
        sf::Color fill_color;

    public:
        // Constructors and Destructors
        Character(sf::Vector2f spawn_pos, sf::Color _fill_color = sf::Color::White, sf::Color outline_color = sf::Color::Black, float outline_thickness = -3.f);
        virtual ~Character();

        // Accessors and Mutators
        float getSpeed() { return max_speed; };
        void setDesVel(sf::Vector2f new_des_vel);
        void setActVel(sf::Vector2f new_act_vel);

        // Functions
        void update();

        // Variables
        sf::Vector2f des_vel = sf::Vector2f(0.f,0.f); // desired velocity
        sf::Vector2f act_vel = sf::Vector2f(0.f,0.f); // actual velocity (taking into account collisions)

        float angle = 0.f;

        int hp = 100;
        bool is_hit = false;

        bool is_attacking = false;
        bool in_collision = false;

        sf::Int64 hit_loop = 300;
        sf::Int64 time_since_last_hit = 0;

};

#endif