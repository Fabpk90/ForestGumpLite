//
// Created by fab on 07/11/18.
//

#include "mapManager.h"

MapManager::MapManager(const char* path)
{
    if(loadFromFile(path))
    {

    }
}

bool MapManager::loadFromFile(const char *path)
{
    return false;
}

void MapManager::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for(auto actor : actorList)
    {
        actor->draw(target, states);
    }
}
