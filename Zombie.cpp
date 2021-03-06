#include "Zombie.h"

Zombie::Zombie(int zid, sf::Vector2f spawn_pos) : Character(spawn_pos, sf::Color::Green)
{
    // instantiates the character superclass but with the color green

    // set the zombie class specific max speed
    this->max_speed = ZOMBIE_SPEED;

    // give the zombie and id to track it
    this->id = zid;
}

void Zombie::goTowards(float x_des, float y_des)
{
    //update the velocities for the zombie so that it goes towards the specified destination
    float x_diff = x_des - this->pos.x;
    float y_diff = y_des - this->pos.y;

    float x_dir = 0.0;
    if (abs(x_diff) > 1.0) {
        x_dir = (x_diff)/abs(x_diff);
    }


    float y_dir = 0.0;
    if (abs(y_diff) > 1.0) {
        y_dir = (y_diff)/abs(y_diff);
    }


    float zombie_speed_x = this->max_speed * x_dir;
    float zombie_speed_y = this->max_speed * y_dir;

    if (abs(y_diff) < zombie_speed_y) {
        zombie_speed_y = y_diff;
    }

    if(abs(x_diff) < zombie_speed_x) {
        zombie_speed_x = x_diff;
    }

    this->setDesVel(sf::Vector2f(zombie_speed_x, zombie_speed_y));
}