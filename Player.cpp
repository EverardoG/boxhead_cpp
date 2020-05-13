#include "Player.h"

Player::Player()
{
    this->x_pos = 400;
    this->y_pos = 400;

    this->render.setPosition(this->x_pos, this->y_pos);
}

// Player::~Player()
// {
//     //shuts down class
// }
