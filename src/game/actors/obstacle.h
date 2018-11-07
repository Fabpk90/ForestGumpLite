//
// Created by fab on 07/11/18.
//

#ifndef FORESTGUMPLITE_OBSTACLE_H
#define FORESTGUMPLITE_OBSTACLE_H


#include "actor.h"

class Obstacle : public Actor
{
private:


public:
    Obstacle(const char* path, int health, sf::Vector2f position);
    void onDie();
};


#endif //FORESTGUMPLITE_OBSTACLE_H
