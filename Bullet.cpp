#include "Bullet.h"

Bullet::Bullet(float startx, float starty, float _angle)
{
    // need to start the bullet path
    // need to know where to put bullet and also where it's going

    this->angle = _angle;

    // start position will always be from the same place relative to player
    // final position will let us interpolate through time where to put bullet
    this->start_x = startx;
    this->start_y = starty;
    this->start_pos = sf::Vector2f(startx, starty);

    // update current position
    this->curr_x = this->start_x;
    this->curr_y = this->start_y;
    this->cur_pos = this->start_pos;

    // find endpoint
    this->end_x = this->start_x + this->final_distance * sin(angle);
    this->end_y = this->start_y + this->final_distance * sin(angle);

    // set up the render
    this->m_render.setFillColor(sf::Color::Black);
    this->m_render.setPosition(sf::Vector2f(this->curr_x, this->curr_y));
    this->m_render.rotate(angle);
    this->m_render.setSize(sf::Vector2f(0.f, 0.f));

    std::cout << "New Bullet - angle: " << this->angle << std::endl;
}

void Bullet::update()
{
    this->cur_pos.x += this->current_distance * cos(angle * PI/180.f);
    this->cur_pos.y += this->current_distance * sin(angle * PI/180.f);

    std::cout << "Bullet x: " << this->cur_pos.x << " | y: " << this->cur_pos.y << std::endl;

    if (this->current_distance < this->final_distance) {
        this->current_distance += this->speed;
        this->m_render.setSize(sf::Vector2f(this->current_distance, 1.f));
    }

    if (this->current_distance >= this->final_distance) {
        this->current_distance = this->final_distance;
        this->finished = true;
    }
}

sf::RectangleShape Bullet::getRender()
{
    return this->m_render;
}