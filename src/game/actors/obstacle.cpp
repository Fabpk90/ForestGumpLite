//
// Created by fab on 07/11/18.
//

#include "obstacle.h"

Obstacle::Obstacle(const char *path, int health, sf::Vector2f position) : Actor(path, health)
{
    sprite->setPosition(position.x, position.y);
}
