#ifndef COLLISIONENGINE_H
#define COLLISIONENGINE_H

#include "dependencies.h"

/* WARNING: CollisionEngine class is NOT tested - if code is not behaving in the way its
    expected to, it could be due to a semantic error in the CollisionEngine class */

class Point
{
    /* A point is simply a vector that represents where a point is */
    public:
        // Constructors and Destructors
        Point(sf::Vector2f _point) { this->x = _point.x; this->y = _point.y; };
        Point operator + (Point point) {
            float x_val = this->x + point.x;
            float y_val = this->y + point.y;
            Point newpoint = Point(sf::Vector2f(x_val, y_val));

        };
        Point operator - (Point point) {
            float x_val = this->x - point.x;
            float y_val = this->y - point.y;
            Point newpoint = Point(sf::Vector2f(x_val, y_val));
            return newpoint;
        };
        float calculateDist() {
            // returns the value of the normalized vector
            return sqrt (pow(this->x, 2) + pow(this->y, 2) );
        }

        float x;
        float y;
};

class Line
{
    /* A line is just two points connected to each other */
    public:
        // Constructors and Destructors
        Line( Point* _start, Point* _finish  ) { this->start = _start; this->finish = _finish; };
        Point* start;
        Point* finish;
        float distance() {
            return (*this->finish - *this->start).calculateDist();
        }
};

class Rect
{
    /* A rectangle is defined by two points that allow you to get the rest of the rectangle */
    /* basically the same as a line, but we are going to treat it differently */
    public:
        // Constructors and Destructors
        Rect( Point* _bottom_left, Point* width_height  ) {
            // set the corners for the rectangle
            this->bottom_left = _bottom_left;
            this->bottom_right = new Point(sf::Vector2f(this->bottom_left->x + width_height->x , this->bottom_left->y));
            this->top_left = new Point(sf::Vector2f(this->bottom_left->x, this->bottom_left->y + width_height->y));
            this->top_right = new Point(sf::Vector2f(this->bottom_left->x + width_height->x, this->bottom_left->y + width_height->y));

            this->bottom = new Line(bottom_left, bottom_right);
            this->top = new Line(top_left, top_right);
            this->left = new Line(bottom_left, top_left);
            this->right = new Line(bottom_right, top_right);
            };

        Point* bottom_left;
        Point* bottom_right;
        Point* top_left;
        Point* top_right;

        Line* bottom;
        Line* top;
        Line* left;
        Line* right;
};

class CollisionEngine
{
    public:
        bool isPointCollision(Point* point1, Point* point2, float err = 0.1f);
        bool isLinePointCollision( Line* line, Point* point, float err = 0.1f );

        bool isLineCollision(Line* line1, Line* line2);
        bool isLineRectCollision(Line* line, Rect* rect);
};

#endif