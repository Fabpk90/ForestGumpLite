//
// Created by fab on 07/11/18.
//
#include "../../util/constants.h"
#include <fstream>
#include <iostream>

#include <ctime>
#include <cstdlib>

#include "mapManager.h"
#include "../actors/obstacle.h"

MapManager::MapManager(const char* path)
{
    if(loadFromFile(path))
    {
        //loads ground
        if(groundTex.loadFromFile("res/texture/ground.png"))
        {
            for (int y = 0; y < PIXEL_COUNT_HEIGHT; ++y)
            {
                for (int x = 0; x < PIXEL_COUNT_WIDTH; ++x)
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

sf::Vector2f MapManager::getFreePosition()
{
    std::srand(std::time(nullptr));
    int x = std::rand() % (PIXEL_COUNT_WIDTH + 1);
    int y = std::rand() % (PIXEL_COUNT_HEIGHT + 1);

    sf::Vector2f pos(x * PIXEL_SIZE, y * PIXEL_SIZE);


    while(!getIsPositionFree(pos))
    {
        x = std::rand() % (PIXEL_COUNT_WIDTH + 1);
        y = std::rand() % (PIXEL_COUNT_HEIGHT + 1);

        pos.x = x * PIXEL_SIZE;
        pos.y = y * PIXEL_SIZE;
    }

    return pos;
}


bool MapManager::addActor(Actor *actor)
{
    if(getIsPositionFree(actor->getPosition()))
    {
        actorList.push_back(actor);
        return true;
    }

    return false;
}

bool MapManager::getIsPositionFree(sf::Vector2f pos)
{
    for(Actor* obj : actorList)
    {
        if(obj->getPosition() == pos)
        {
            return false;
        }
    }

    return true;
}
