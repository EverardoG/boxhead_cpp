#include "Character.h"

Character::Character(sf::Vector2f spawn_pos, sf::Color fill_color, sf::Color outline_color, float outline_thickness)
{
    // set up the render and spawn the character

    // sets color of render
    this->render.setFillColor(fill_color);
    this->render.setOutlineColor(outline_color);
    this->render.setOutlineThickness(outline_thickness);

    // sets size of render and places character
    this->render.setSize(sf::Vector2f(this->width, this->height));
    this->pos = spawn_pos;
    this->render.setPosition(this->pos);
}

Character::~Character()
{
    //shuts down class
}

void Character::update()
{

    float new_x_pos = this->pos.x + this->des_vel.x;
    float new_y_pos = this->pos.y + this->des_vel.y;

    bool character_is_moving = true;
    if (new_x_pos - this->pos.x + new_y_pos - this->pos.y == 0.0f){
        character_is_moving = false;
    }

    //update where the character is facing (for attacking)
    if (character_is_moving) {
        if (new_x_pos == this->pos.x) {
            this->dir.x = 0;
        }
        else if (this->des_vel.x != 0.f) {
            this->dir.x = this->des_vel.x/(abs(this->des_vel.x));
        }

        if (new_y_pos == this->pos.y) {
            this->dir.x = 0;
        }
        else if (this->des_vel.y != 0.f) {
            this->dir.y = this->des_vel.y/(abs(this->des_vel.y));
        }
    }

    // update the angle of the character using the directions in x and y
    this->angle = atan2(this->dir.y, this->dir.x) * 180.f/PI;

    // update the position of the character
    this->pos.x += this->des_vel.x;
    this->pos.y += this->des_vel.y;

    // and update the render
    this->render.setPosition(sf::Vector2f(pos.x,pos.y));
}

void Character::setDesVel(sf::Vector2f new_des_vel)
{
    this->des_vel = new_des_vel;
}

void Character::setActVel(sf::Vector2f new_act_vel)
{
    this->act_vel = new_act_vel;
}
