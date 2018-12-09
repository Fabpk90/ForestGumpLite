//
// Created by fab on 06/12/2018.
//

#include <cmath>
#include "VectorHelper.h"

float VectorHelper::getLength(float x, float y) {
    return sqrt((x*x) + (y*y));
    //TODO: change to a more efficient square method
}

float VectorHelper::getDotProduct(float x0, float y0, float x1, float y1) {
    return (x0 * x1) + (y0 * y1);
}

sf::Vector2f VectorHelper::normalize(sf::Vector2f v)
{
    float length = getLength(v.x, v.y);

    v.x /= length;
    v.y /= length;

    return v;
}
