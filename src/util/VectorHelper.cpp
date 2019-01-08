//
// Created by fab on 06/12/2018.
//

#include <cmath>
#include "VectorHelper.h"

float VectorHelper::getLength(float x, float y) {
    return sqrt((x*x) + (y*y));
}


float VectorHelper::getLength(sf::Vector2f v) {
    return sqrt((v.x * v.x) + (v.y * v.y));
}

float VectorHelper::getDotProduct(float x0, float y0, float x1, float y1) {
    return (x0 * x1) + (y0 * y1);
}

sf::Vector2f VectorHelper::normalize(sf::Vector2f v)
{
    float length = getLength(v.x, v.y);
    if(length != 0)
    {
        v.x /= length;
        v.y /= length;
    }

    return v;
}

float VectorHelper::angleBetween(sf::Vector2f v1, sf::Vector2f v2) {
    return atan2(v1.y, v1.x) - atan2(v2.y, v2.x);;
}

