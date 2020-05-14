#include "Player.h"

Player::Player(sf::Vector2f spawn_pos) : Character(spawn_pos)
{
    // set max_speed to player's max_speed
    this->max_speed = PLAYER_SPEED;

    // instantiation of Character class handles spawning
}