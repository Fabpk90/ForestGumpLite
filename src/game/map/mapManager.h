//
// Created by fab on 07/11/18.
//

#ifndef FORESTGUMPLITE_MAPMANAGER_H
#define FORESTGUMPLITE_MAPMANAGER_H

#include <vector>
#include "../actors/actor.h"

using namespace std;

class MapManager
{
private:
    vector<Actor*> map;

public:
    MapManager();

    //TODO: loader de map
};


#endif //FORESTGUMPLITE_MAPMANAGER_H
