#include "Bullet.h"

Bullet::Bullet(float startx, float starty, float angle)
{
    // need to start the bullet path
    // need to know where to put bullet and also where it's going

    // start position will always be from the same place relative to player
    // final position will let us interpolate through time where to put bullet
    this->start_x = startx;
    this->start_y = starty;

    // update current position
    this->curr_x = this->start_x;
    this->curr_y = this->start_y;

    // find endpoint
    this->end_x = this->start_x + this->final_distance * sin(angle);
    this->end_y = this->start_y + this->final_distance * sin(angle);

    // set up the render
    this->render.setFillColor(sf::Color::Black);
    this->render.setPosition(sf::Vector2f(this->curr_x, this->curr_y));
    this->render.rotate(angle);
    this->render.setSize(sf::Vector2f(0.f, 0.f));
}

void Bullet::update()
{

    if (this->current_distance < this->final_distance) {
        this->current_distance += this->speed;
        this->render.setSize(sf::Vector2f(this->current_distance, 1.f));
    }

    if (this->current_distance >= this->final_distance) {
        this->current_distance = this->final_distance;
        this->finished = true;
    }


}