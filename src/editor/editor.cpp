//
// Created by fab on 28/11/18.
//

#include "editor.h"
#include "../game/gameManager.h"
#include "../util/Constants.h"
#include "../game/actors/obstacle.h"
#include <iostream>



void Editor::update()
{
    sf::RenderWindow& window = GameManager::Instance->getWindow();
		

    window.clear(GameManager::Instance->getClearColor());
    window.draw(mapManager);

    window.display();

		for(auto actor : obstaclesP)
		{
			winPalette->draw(actor->getSprite());
		}
		sf::Event eventPal;
    
		
		winPalette->display();
		winPalette->clear(clearColor);
		
		while (winPalette->pollEvent(eventPal))//crash
		{

			if (eventPal.type == sf::Event::MouseButtonReleased)							
					brushSelect(*winPalette);													
		}																				
																				
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			winPalette->close();
	
		
		
    sf::Event event;
    while (window.pollEvent(event))
    {
		if (event.type == sf::Event::MouseButtonReleased)							
			paint(window);		
															
    }																				
																					
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();															
}
																					
Editor::~Editor()																	
{																					
																					
}																					
																					
Editor::Editor()															
{																					
    mapManager.setDrawLines(true);				
    
	winPalette = new sf::RenderWindow(sf::VideoMode(64, 128), "Palette");
	obstaclesP.push_back(new Obstacle("res/texture/tree.png", 1, 0, 0));
    obstaclesP.push_back(new Obstacle("res/texture/rock.png", 1, 32, 0));
    winPalette->setKeyRepeatEnabled(false);													
    clearColor.r = 0;
    clearColor.g = 0;
    clearColor.b = 0;										
    brushType = 0;																	
}

void Editor::paint(sf::RenderWindow& window)
{
	std::cout << "bonjour\n";
	
	sf::Vector2i mouse = sf::Mouse::getPosition(window);
	int BoundX = mouse.x - (mouse.x % PIXEL_SIZE);
	int BoundY = mouse.y - (mouse.y % PIXEL_SIZE);
	bool isFound = false;
	
	std::cout << BoundX << " " << mouse.x << " / " << BoundY << " " << mouse.y << std::endl;
	std::list<Actor*>::iterator actor = mapManager.getActorList().begin();
	while(actor != mapManager.getActorList().end())
	{
		
		if (BoundX <= (*actor)->getPosition().x &&											
			BoundX + PIXEL_SIZE > (*actor)->getPosition().x &&
			BoundY <= (*actor)->getPosition().y &&
			BoundY + PIXEL_SIZE  > (*actor)->getPosition().y)
		{
			mapManager.getActorList().erase(actor++);
			isFound = true;
			std::cout << "BOOM\n";
		}
		++actor;
	}
	if(!isFound)
	{
		switch(brushType)
		{
			case TILE_TREE:
				mapManager.addActor(new Obstacle("res/texture/tree.png", 1, BoundX, BoundY)); //add health amount choice
			break;

			case TILE_ROCK:
				mapManager.addActor(new Obstacle("res/texture/rock.png", 1, BoundX, BoundY));
			break;
		}
	}
}

void Editor::brushSelect(sf::RenderWindow& window)
{
	sf::Vector2i mouse = sf::Mouse::getPosition(window);
	int BoundX = mouse.x;
	int BoundY = mouse.y;
	std::cout << mouse.x << " / " << mouse.y << std::endl;
	if(BoundX >= 0 && BoundX <= 32 && BoundY >= 0 && BoundY <= 32)
	brushType = TILE_TREE;
	if(BoundX > 32 && BoundX <= 64 && BoundY >= 0 && BoundY <= 32)
	brushType = TILE_ROCK;
}
