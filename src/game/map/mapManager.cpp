//
// Created by fab on 07/11/18.
//
#include "../../util/constants.h"
#include <fstream>
#include <iostream>

#include "mapManager.h"
#include "../actors/obstacle.h"

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
    int x = 0, y = 0;

    if(file.is_open())
    {
        while(file >> tileValue)
        {
            if(x == PIXEL_COUNT_WIDTH)
            {
                y++; x = 0;
            }

            switch(tileValue)
            {
                case 1: //TREE
                    actorList.push_back(new Obstacle("res/texture/tree.png", 10, x * PIXEL_SIZE, y * PIXEL_SIZE));
                break;

                case 2: //ROCK

                break;

                case 3: //PLAYER1

                break;

                case 4: //PLAYER 2

                break;
            }

            x++;
        }

        file.close();

        return true;
    }
    else //TODO: Error handling
        return false;


}

void MapManager::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for(auto actor : actorList)
    {
        actor->draw(target, states);
    }
}

MapManager::~MapManager()
{
    for(auto actor : actorList)
    {
        delete actor;
    }
}
