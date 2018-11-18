//
// Created by fab on 07/11/18.
//

#include <fstream>
#include <iostream>

#include "mapManager.h"

MapManager::MapManager(const char* path)
{
    if(loadFromFile(path))
    {

    }
}

bool MapManager::loadFromFile(const char *path)
{
    std::ifstream file(path);
    int tileValue = 0;

    if(file.is_open())
    {
       /* while(file >> tileValue)
        {
            std::cout << tileValue;
        }*/

        file.close();

        return true;
    }

    std::cout << "shiet";

    return false;
}

void MapManager::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for(auto actor : actorList)
    {
        actor->draw(target, states);
    }
}
