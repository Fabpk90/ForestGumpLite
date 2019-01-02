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
																					
Editor::Editor() : thread(&Editor::palette, this)															
{																					
    mapManager.setDrawLines(true);				
	thread.launch();												
    brushType = 0;																	
}

void Editor::palette()
{
	sf::RenderWindow* winPalette = new sf::RenderWindow(sf::VideoMode(128, 500), "Palette");	
	
    winPalette->setKeyRepeatEnabled(false);													
    clearColor.r = 0;
    clearColor.g = 0;
    clearColor.b = 0;
    
    list<Actor*> obstacles;
    obstacles.push_back(new Obstacle("res/texture/tree.png", 1, 0, 0));
    obstacles.push_back(new Obstacle("res/texture/rock.png", 1, 64, 0));	
    													
    sf::Event eventPal;
    
    while (winPalette->isOpen())//crash
    {	
		for(auto actor : obstacles)
		{
			winPalette->draw(actor->getSprite());
		}
		winPalette->display();
		winPalette->clear(clearColor);
		
		while (winPalette->pollEvent(eventPal))//crash
		{

			if (eventPal.type == sf::Event::MouseButtonReleased)							
					std::cout << "lol\n";														
		}																				
																				
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			winPalette->close();	
	}
	
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

			break;
		}
	}
}
