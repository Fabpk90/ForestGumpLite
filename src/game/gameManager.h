//
// Created by fab on 07/11/18.
//

#ifndef FORESTGUMPLITE_GAMEMANAGER_H
#define FORESTGUMPLITE_GAMEMANAGER_H

#include "map/mapManager.h"

class GameManager
{
private:
    MapManager* mapManager;

public:
    GameManager();
    static GameManager* Instance;
};




#endif //FORESTGUMPLITE_GAMEMANAGER_H
