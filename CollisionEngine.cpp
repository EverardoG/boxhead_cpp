#include "CollisionEngine.h"

bool CollisionEngine::isPointCollision(Point* point1, Point* point2, float err)
{
    float distance = sqrt( pow( point1->x - point2->x , 2) + pow( point1->y - point2->y , 2 ) );
    if ( abs(distance) < abs(err) ) {
        return true;
    }
    else {
        return false;
    }
}

bool CollisionEngine::isLinePointCollision(Line* line, Point* point, float err)
{
    float start_to_pt = (*point - *(line->start)).calculateDist(); // from start of the line to the point
    float end_to_pt = (*point - *(line->start)).calculateDist();
    float line_length = line->distance();

    if ( start_to_pt + end_to_pt >= line_length + err ) {
        return true;
    }
    else {
        return false;
    }
}

bool CollisionEngine::isLineCollision(Line* line1, Line* line2)
{
    float x1 = line1->start->x;  float y1 = line1->start->y;
    float x2 = line1->finish->x; float y2 = line1->finish->y;
    float x3 = line2->start->x;  float y3 = line2->start->y;
    float x4 = line2->finish->x; float y4 = line2->finish->y;


    float uA = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
    float uB = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));

    if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {
        float intersectionX = x1 + (uA * (x2-x1));
        float intersectionY = y1 + (uA * (y2-y1));
        return true;
    }
    else {
        return false;
    }
}

bool CollisionEngine::isLineRectCollision(Line* line, Rect* rect)
{
    return ( isLineCollision(line, rect->top)
            || isLineCollision(line, rect->left)
            || isLineCollision(line, rect->right)
            || isLineCollision(line, rect->bottom));
}