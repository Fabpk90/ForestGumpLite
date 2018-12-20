//
// Created by fab on 06/12/2018.
//

#ifndef FORESTGUMPLITE_VECTORHELPER_H
#define FORESTGUMPLITE_VECTORHELPER_H


#include <SFML/System.hpp>



class VectorHelper {
public:
    static float getLength(float x, float y);
    static float getLength(sf::Vector2f v);
    static float getDotProduct(float x0, float y0, float x1, float y1);
    static sf::Vector2f normalize(sf::Vector2f v);
    static float angleBetween(sf::Vector2f v1, sf::Vector2f v2);
};


#endif //FORESTGUMPLITE_VECTORHELPER_H
