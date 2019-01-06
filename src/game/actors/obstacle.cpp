//
// Created by fab on 07/11/18.
//

#include "obstacle.h"
#include "../gameManager.h"

Obstacle::Obstacle(const char *path, int health, int x, int y, int type) : Actor(path, health)
{
    sprite.setPosition(x, y);
    this->type = type;
}

int Obstacle::getType()
{
	return type;
}

void Obstacle::setType(int type)
{
	this->type = type;
}

void Obstacle::onDie()
{
    //GameManager::Instance
}
