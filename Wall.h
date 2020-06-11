/*
Class for encapsulating objects on the screen that have a collision box
and a render, but don't move
 */

#ifndef WALL_H
#define WALL_H

#include "dependencies.h"
#include "InGameObject.h"

class Wall : public InGameObject
{
    protected:
        sf::Vector2f size;
        sf::RectangleShape m_render; // this is called shape in the tutorials
        sf::Vector2f pos; // positionsi

    public:
        // Constructors and Destructors
        Wall(sf::Vector2f _pos, sf::Vector2f _size, sf::Color _fill_color = sf::Color::White, sf::Color _outline_color = sf::Color::Black, float _outline_thickness = -3.f);
        virtual ~Wall();

        // functions
        void update();

};

#endif