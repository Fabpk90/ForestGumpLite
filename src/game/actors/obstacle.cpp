//
// Created by fab on 07/11/18.
//

#include "obstacle.h"
#include "../gameManager.h"

Obstacle::Obstacle(const char *path, int health, int x, int y) : Actor(path, health)
{
    sprite.setPosition(x, y);
}

void Obstacle::onDie()
{
    //GameManager::Instance
}
