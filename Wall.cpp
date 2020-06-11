#include "Wall.h"

Wall::Wall(sf::Vector2f _pos, sf::Vector2f _size, sf::Color _fill_color, sf::Color _outline_color, float _outline_thickness)
{
    // save the position and size
    this->pos = _pos;
    this->size = _size;

    // set up the render
    this->m_render.setPosition(this->pos);
    this->m_render.setSize(this->size);

    this->m_render.setFillColor(_fill_color);
    this->m_render.setOutlineColor(_outline_color);
    this->m_render.setOutlineThickness(_outline_thickness);

    collision_shape = Rect(new Point(pos), new Point(size));
}

Wall::~Wall()
{

}

void Wall::update()
{
    // do nothing, as this is a Wall
    // may add some animation later
}
