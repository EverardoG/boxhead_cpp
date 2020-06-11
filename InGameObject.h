/*
    Class for encapsulating the abstract character class
    This class is inherited by the zombie and player classes
 */

#ifndef INGAMEOBJ_H
#define INGAMEOBJ_H

#include"dependencies.h"
#include "CollisionEngine.h"

class InGameObject
{
    protected:
        sf::Vector2f size;
        sf::RectangleShape m_render; // this is called shape in the tutorials
        sf::Vector2f pos; // position
        CollisionShape collision_shape;

    public:
        // Accessors and Mutators
        sf::Vector2f getPos()  { return pos; };
        sf::Vector2f getSize() { return size; };
        sf::RectangleShape getRender() { return m_render; };
        CollisionShape getCollisionShape() {return collision_shape; }

        // Functions
        virtual void update() = 0;
};

#endif