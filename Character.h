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
        const sf::Vector2f size = CHARACTER_SIZE;
        sf::RectangleShape m_render; // this is called shape in the tutorials
        sf::Vector2f pos; // position
        float max_speed = 1.f;

    public:
        // Constructors and Destructors
        Character(sf::Vector2f spawn_pos, sf::Color fill_color = sf::Color::White, sf::Color outline_color = sf::Color::Black, float outline_thickness = -3.f);
        virtual ~Character();

        // Accessors and Mutators
        sf::Vector2f getPos();
        sf::Vector2f getSize();
        sf::RectangleShape getRender();
        float getSpeed();
        void setDesVel(sf::Vector2f new_des_vel);
        void setActVel(sf::Vector2f new_act_vel);

        // Functions
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