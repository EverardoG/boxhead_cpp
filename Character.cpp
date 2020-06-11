#include "Character.h"

Character::Character(sf::Vector2f spawn_pos, sf::Color _fill_color, sf::Color outline_color, float outline_thickness)
{
    // set up the render and spawn the character
    this->size = CHARACTER_SIZE;
    this->pos = spawn_pos;

    // sets color of render
    this->fill_color = _fill_color;
    this->m_render.setFillColor(this->fill_color);
    this->m_render.setOutlineColor(outline_color);
    this->m_render.setOutlineThickness(outline_thickness);

    // sets size of render and places character
    this->m_render.setSize(this->size);
    this->m_render.setPosition(this->pos);

    this->collision_shape = Rect( new Point(pos), new Point(size) );
}

Character::~Character()
{
    //shuts down class
}

void Character::update()
{
    // update the direction based on the character's

    // update the angle based on the character's desired velocity
    if (this->des_vel.x != 0 || this->des_vel.y != 0) {
        this->angle = atan2(int(this->des_vel.y), int(this->des_vel.x)) * 180.f/PI;
    }

    // update the character's position based on the character's actual velocity
    this->pos.x += this->act_vel.x;
    this->pos.y += this->act_vel.y;

    // and update the render
    this->m_render.setPosition(sf::Vector2f(pos.x,pos.y));

    // also check if this character is taking damage and make them red if so
    if (this->is_hit) {
        this->m_render.setFillColor(sf::Color::Red);
    }
    else {
        this->m_render.setFillColor(this->fill_color);
    }
}

void Character::setDesVel(sf::Vector2f new_des_vel)
{
    this->des_vel = new_des_vel;
}

void Character::setActVel(sf::Vector2f new_act_vel)
{
    this->act_vel = new_act_vel;
}