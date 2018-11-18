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
        //loads ground
        if(groundTex.loadFromFile("res/texture/ground.png"))
        {
            for (int y = 0; y < SCREEN_SIZE_HEIGHT / PIXEL_SIZE; ++y)
            {
                for (int x = 0; x < SCREEN_SIZE_WIDTH / PIXEL_SIZE; ++x)
                {
                    sf::Sprite* sprite = new sf::Sprite(groundTex);
                    sprite->setPosition(y * PIXEL_SIZE, x * PIXEL_SIZE); // because sfml start at the top left corner

                    groundList.push_back(sprite);
                }
            }
        }
        else
        {
            std::cout << "error loading ground texture";
        }

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
    for(auto ground : groundList)
    {
        target.draw(*ground);
    }

    for(auto actor : actorList)
    {
        actor->draw(target, states);
    }
}

MapManager::~MapManager()
{
    for(auto ground : groundList)
    {
        delete ground;
    }

    for(auto actor : actorList)
    {
        delete actor;
    }
}
