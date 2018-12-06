//
// Created by fab on 06/12/2018.
//

#ifndef FORESTGUMPLITE_VECTORHELPER_H
#define FORESTGUMPLITE_VECTORHELPER_H


#include <SFML/System.hpp>

#define PI 3.14159265

class VectorHelper {
public:
    static float getLength(float x, float y);
    static float getDotProduct(float x0, float y0, float x1, float y1);
};


#endif //FORESTGUMPLITE_VECTORHELPER_H
