//
// Created by fab on 07/11/18.
//
#include "../util/constants.h"
#include <fstream>
#include <iostream>

#include <ctime>
#include <cstdlib>
#include <cassert>

#include "mapManager.h"
#include "../game/actors/obstacle.h"
#include "../game/gameManager.h"



MapManager::MapManager() : drawLines(false)
{
    loadLines();

    std::srand(std::time(nullptr));
}

MapManager::MapManager(const char* path) : drawLines(false)
{
    std::srand(std::time(nullptr));

    loadLines();

    if(!loadMapFromFile(path))
    {
        std::cerr << "Unable to load the map from " << path;
    }
}

bool MapManager::loadMapFromFile(const char *path)
{
    std::ifstream file(path);
    int tileValue = 0, tilePosNrmx, tilePosNrmy;

    if(file.is_open())
    {
        while(file >> tileValue)
        {
            if(!file.eof())
                file >> tilePosNrmx;
            else
                assert(false);

            if(!file.eof())
                file >> tilePosNrmy;
            else
                assert(false);

            switch(tileValue)
            {
                case TILE_TREE:
                    actorList.push_back(new Obstacle("res/texture/tree.png", 2, tilePosNrmx * PIXEL_SIZE, tilePosNrmy * PIXEL_SIZE));
                break;

                case TILE_ROCK:

                break;
            }
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

    if(drawLines)
        target.draw(lineVertexPoints);
}

MapManager::~MapManager()
{
    for(auto actor : actorList)
    {
        delete actor;
    }
}

sf::Vector2f MapManager::getFreePosition()
{
    int x = std::rand() % (PIXEL_COUNT_WIDTH);
    int y = std::rand() % (PIXEL_COUNT_HEIGHT);

    sf::Vector2f pos(x * PIXEL_SIZE, y * PIXEL_SIZE);


    while(!getIsPositionFree(pos))
    {
        x = std::rand() % (PIXEL_COUNT_WIDTH);
        y = std::rand() % (PIXEL_COUNT_HEIGHT);

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

void MapManager::loadLines()
{
    sf::RenderWindow& window = GameManager::Instance->getWindow();

    lineVertexPoints.setPrimitiveType(sf::PrimitiveType::Lines);

    sf::Vertex vertex;

    float sizeY = window.getSize().y / PIXEL_SIZE;
    float sizeX = window.getSize().x / PIXEL_SIZE;

    for (int i = 0; i < sizeY; ++i)
    {
        //first point of the line
        vertex.position = sf::Vector2f(0, i * PIXEL_SIZE);
        lineVertexPoints.append(vertex);

        //second point
        vertex.position = sf::Vector2f(window.getSize().x, i * PIXEL_SIZE);
        lineVertexPoints.append(vertex);

    }

    for (int i = 0; i < sizeX; ++i)
    {
        //first point of the line
        vertex.position = sf::Vector2f(i * PIXEL_SIZE, 0);
        lineVertexPoints.append(vertex);

        //second point
        vertex.position = sf::Vector2f(i * PIXEL_SIZE, window.getSize().y);
        lineVertexPoints.append(vertex);

    }

}

bool MapManager::collisionCheck(sf::FloatRect rect, Player &playerAiming) {
    bool didCollide = false;
    auto actor = actorList.begin();

    while(actor != actorList.end())
    {
        if (rect.intersects((*actor)->getGlobalBounds()))
        {
            auto player = dynamic_cast<Player*>(*actor);

            if(!player || player->isPlayerOne() != playerAiming.isPlayerOne())
            {
                didCollide = true;

                if((*actor)->takeDamage(1))
                {
                    delete *actor;
                    actor = actorList.erase(actor);
                }
                else
                    ++actor;
            }
            else
                ++actor;
        }
        else
            ++actor;
    }

    return didCollide;
}
