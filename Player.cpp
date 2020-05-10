#include "Player.h"
#define PI 3.14159265
#include <math.h>

Player::Player()
{
    // instantiates the class
    this->initVariables();
}

Player::~Player()
{
    //shuts down class
}

void Player::initVariables()
{
    // this->render.setPosition(sf::Vector2f(100.f,100.f));
    this->render.setSize(sf::Vector2f(this->width, this->height));
    this->render.setFillColor(sf::Color::Blue);
    this->render.setOutlineColor(sf::Color::Black);
    this->render.setOutlineThickness(3.f);
}

void Player::update()
{

    float new_x_pos = this->x_pos + this->x_vel;
    float new_y_pos = this->y_pos + this->y_vel;

    bool player_is_moving = true;
    if (new_x_pos - this->x_pos + new_y_pos - this->y_pos == 0.0f){
        player_is_moving = false;
    }

    //update where the player is facing (for attacking)
    if (player_is_moving) {
        if (new_x_pos == this->x_pos) {
            this->direction_x = 0;
        }
        else if (this->x_vel != 0.f) {
            this->direction_x = this->x_vel/(abs(this->x_vel));
        }

        if (new_y_pos == this->y_pos) {
            this->direction_y = 0;
        }
        else if (this->y_vel != 0.f) {
            this->direction_y = this->y_vel/(abs(this->y_vel));
        }
    }

    // update the angle of the player using the directions in x and y
    this->angle = atan2(direction_y, direction_x) * 180/PI;

    // update the position of the player
    this->x_pos += this->x_vel;
    this->y_pos += this->y_vel;

    // if the x direction is update, and not the y, then I know the y is zero

    // if the y direction is updated, and the x not, then I know x is zero

    // std::cout << this->direction_x << " | " << this->direction_y << std::endl;
    // std::cout << this->angle << std::endl;

    // and update the render

    this->render.setPosition(sf::Vector2f(x_pos,y_pos));
}

void Player::updateVel(float new_x_vel, float new_y_vel)
{
    this->x_vel = new_x_vel;
    this->y_vel = new_y_vel;
}
