#include "Character.h"

Character::Character(sf::Color fill_color, sf::Color outline_color, float outline_thickness)
{
    // instantiates the class
    this->render.setSize(sf::Vector2f(this->width, this->height));
    this->render.setFillColor(fill_color);
    this->render.setOutlineColor(outline_color);
    this->render.setOutlineThickness(outline_thickness);
}

Character::~Character()
{
    //shuts down class
}

void Character::update()
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

    // and update the render
    this->render.setPosition(sf::Vector2f(x_pos,y_pos));
}

void Character::updateVel(float new_x_vel, float new_y_vel)
{
    this->x_vel = new_x_vel;
    this->y_vel = new_y_vel;
}
