/*
    Class for encapsulating the player object
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "dependencies.h"
#include "Character.h"

class Player : public Character
{
    public:
        Player(sf::Vector2f spawn_pos);
};

#endif