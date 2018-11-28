//
// Created by fab on 07/11/18.
//

#ifndef FORESTGUMPLITE_OBSTACLE_H
#define FORESTGUMPLITE_OBSTACLE_H

#include "../../map/mapManager.h"
#include "actor.h"

class Obstacle : public Actor
{
public:
    Obstacle(const char* path, int health, int x, int y);
    void onDie();
};


#endif //FORESTGUMPLITE_OBSTACLE_H
