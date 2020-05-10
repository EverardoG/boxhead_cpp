#include "Zombie.h"
#define PI 3.14159265
#include <math.h>

Zombie::Zombie()
{
    // instantiates the class
    this->initVariables();
}

Zombie::~Zombie()
{
    //shuts down class
}

void Zombie::initVariables()
{
    // randomly place the zombie
    this->x_pos = rand() % 600;
    this->y_pos = rand() % 800;

    this->render.setPosition(sf::Vector2f(this->x_pos,this->y_pos));
    this->render.setSize(sf::Vector2f(this->width, this->height));
    this->render.setFillColor(sf::Color::Green);
    this->render.setOutlineColor(sf::Color::Black);
    this->render.setOutlineThickness(3.f);

}

void Zombie::update()
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
    std::cout << this->angle << std::endl;

    // and update the render

    this->render.setPosition(sf::Vector2f(x_pos,y_pos));
}

void Zombie::updateVel(float new_x_vel, float new_y_vel)
{
    this->x_vel = new_x_vel;
    this->y_vel = new_y_vel;
}
