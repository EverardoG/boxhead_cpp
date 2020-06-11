#include "Bullet.h"

Bullet::Bullet(sf::Vector2f _start_pos, float _angle)
{
    // need to start the bullet path
    // need to know where to put bullet and also where it's going

    this->angle = _angle;

    // start position will always be from the same place relative to player
    // final position will let us interpolate through time where to put bullet
    this->start_pos = _start_pos;

    // update current position
    this->cur_pos = this->start_pos;

    // set up the render
    this->m_render.setFillColor(sf::Color::Black);
    this->m_render.setPosition(start_pos);
    this->m_render.rotate(angle);
    this->m_render.setSize(sf::Vector2f(0.f, 0.f));

    std::cout << "New Bullet - angle: " << this->angle << std::endl;
}

void Bullet::update()
{
    this->cur_pos.x += this->current_distance * cos(angle * PI/180.f);
    this->cur_pos.y += this->current_distance * sin(angle * PI/180.f);

    // update its collision boundary
    this->collision_shape = Line( new Point(start_pos), new Point(cur_pos) );

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