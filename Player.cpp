#include "Player.h"

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
    this->render.setSize(sf::Vector2f(50.f, 100.f));
    this->render.setFillColor(sf::Color::Blue);
    this->render.setOutlineColor(sf::Color::Black);
    this->render.setOutlineThickness(3.f);
}

void Player::update()
{
    this->x_pos += this->x_vel;
    this->y_pos += this->y_vel;

    // and update the render

    this->render.setPosition(sf::Vector2f(x_pos,y_pos));
}

void Player::updateVel(float new_x_vel, float new_y_vel)
{
    this->x_vel = new_x_vel;
    this->y_vel = new_y_vel;
}
