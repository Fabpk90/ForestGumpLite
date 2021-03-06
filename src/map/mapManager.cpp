//
// Created by fab on 07/11/18.
//
#include "../util/Constants.h"
#include <fstream>
#include <iostream>

#include <ctime>
#include <cstdlib>
#include <cassert>

#include "mapManager.h"
#include "../game/actors/obstacle.h"
#include "../game/gameManager.h"
#include "../util/Collision.h"


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
   int tileValue = 0, Health, X, Y;
	if(file.is_open())
	{
		while(file >> tileValue)
		{
			if(!file.eof())
				file >> X;
			else
				assert(false);

			if(!file.eof())
				file >> Y;
			else
				assert(false);
			
			 if(!file.eof())
				file >> Health;
			else
				assert(false);
				
			switch(tileValue)
			{
				case TILE_TREE:
					actorList.push_back(new Obstacle("res/texture/tree.png", Health, X * PIXEL_SIZE, Y * PIXEL_SIZE, TILE_TREE));
					break;
					
				case TILE_TREE_BIG:
					actorList.push_back(new Obstacle("res/texture/BTree.png", Health, X * PIXEL_SIZE, Y * PIXEL_SIZE, TILE_TREE_BIG));
					break;
					
				case TILE_ROCK:
					actorList.push_back(new Obstacle("res/texture/rock.png", Health, X * PIXEL_SIZE, Y * PIXEL_SIZE, TILE_ROCK));
					break;
					
				case TILE_ROCK_BIG:
					actorList.push_back(new Obstacle("res/texture/BRock.png", Health, X * PIXEL_SIZE, Y * PIXEL_SIZE, TILE_ROCK_BIG));
					break;

				default:
					std::cerr << "Identifiant de l'entité non reconnu";
					exit(-1);
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

    if(x & 1) x = -x;
    if(y & 1) y = -y;

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
    sf::RectangleShape rect;
    rect.setPosition(pos);
    rect.setSize(sf::Vector2f(PIXEL_SIZE, PIXEL_SIZE));

    for(Actor* obj : actorList)
    {
        if(obj->getGlobalBounds().intersects(rect.getGlobalBounds()))
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
    
	int X = window.getSize().x;
	int Y = window.getSize().y;
	
    float sizeY = window.getSize().y / PIXEL_SIZE;
    float sizeX = window.getSize().x / PIXEL_SIZE;

    for (int i = -sizeY; i < sizeY; ++i)
    {
        //first point of the line
        vertex.position = sf::Vector2f(-X, i * PIXEL_SIZE);
        lineVertexPoints.append(vertex);

        //second point
        vertex.position = sf::Vector2f(window.getSize().x, i * PIXEL_SIZE);
        lineVertexPoints.append(vertex);
    }

    for (int i = -sizeX; i < sizeX; ++i)
    {
        //first point of the line
        vertex.position = sf::Vector2f(i * PIXEL_SIZE, -Y);
        lineVertexPoints.append(vertex);

        //second point
        vertex.position = sf::Vector2f(i * PIXEL_SIZE, window.getSize().y);
        lineVertexPoints.append(vertex);
    }
}

bool MapManager::collisionAimCheck(Player &playerAiming) {
    bool didCollide = false;
    auto actor = actorList.begin();

    auto aimingRect =  playerAiming.getAimRectangle();
    auto aimingCircleBound = playerAiming.getAimCircle().getGlobalBounds();

    while(actor != actorList.end())
    {
        if (Collision::BoundingBoxTest((*actor)->getSprite(), aimingRect)
        || (*actor)->getSprite().getGlobalBounds().intersects(aimingCircleBound))
        {
            auto player = dynamic_cast<Player*>(*actor);

            if(!player || player->isPlayerOne() != playerAiming.isPlayerOne())
            {
                didCollide = true;

                if((*actor)->takeDamage(playerAiming.getPowerInUse()))
                {
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

    //applying the damage equals to the power
    playerAiming.takeSelfDamage(playerAiming.getPowerInUse());

    return didCollide;
}
