//
// Created by fab on 07/11/18.
//

#include "obstacle.h"

Obstacle::Obstacle(const char *path, int health, float x, float y) : Actor(path, health)
{
    sprite->setPosition(x, y);
}

void Obstacle::onDie()
{

}
