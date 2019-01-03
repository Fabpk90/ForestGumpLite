//
// Created by fab on 28/11/18.
//

#include "editor.h"
#include "../game/gameManager.h"
#include "../util/Constants.h"
#include "../game/actors/obstacle.h"
#include <iostream>
#include <fstream>
#include <string>



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
	GameManager::Instance->getWindow()
	.setView(GameManager::Instance->getWindow().getDefaultView());
}																					
																					
Editor::Editor()															
{																					
    mapManager.setDrawLines(true);				
    
	winPalette = new sf::RenderWindow(sf::VideoMode(64, 128), "Palette");
	//TODO: Load all that from a file "catalog"
	obstaclesP.push_back(new Obstacle("res/texture/tree.png", 1, 0, 0, 1));
    obstaclesP.push_back(new Obstacle("res/texture/rock.png", 1, 32, 0, 2));
    winPalette->setKeyRepeatEnabled(false);													
    clearColor.r = 0;
    clearColor.g = 0;
    clearColor.b = 0;										
    brushType = 0;

    view.setCenter(0, 0);
    view.setSize(sf::Vector2f(GameManager::Instance->getWindow().getSize()));
    GameManager::Instance->getWindow().setView(view);
}

void Editor::paint(sf::RenderWindow& window)
{
	std::cout << "bonjour\n";
	
	sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	int BoundX = 0, BoundY = 0;

	float pixPosX = (mouse.x / PIXEL_SIZE);
	float pixPosY = (mouse.y / PIXEL_SIZE);

	//this is needed when the pos is neg, because of the flooring of the cast
	if(pixPosX < 0)
		pixPosX--;
	if(pixPosY < 0)
		pixPosY--;

	BoundX = (int)pixPosX * PIXEL_SIZE;
	BoundY = (int)pixPosY * PIXEL_SIZE;


	bool isFound = false;
	
	std::cout << BoundX << " " << mouse.x << " / " << BoundY << " " << mouse.y << std::endl;
	std::list<Actor*>::iterator actor = mapManager.getActorList().begin();
	while(actor != mapManager.getActorList().end())
	{
		
		if (BoundX ==(*actor)->getPosition().x
		 && BoundY ==  (*actor)->getPosition().y)
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
				mapManager.addActor(new Obstacle("res/texture/tree.png", 1, BoundX, BoundY, TILE_TREE)); //add health amount choice
			break;

			case TILE_ROCK:
				mapManager.addActor(new Obstacle("res/texture/rock.png", 1, BoundX, BoundY, TILE_ROCK));
			break;
		}
	}
}

void Editor::brushSelect(sf::RenderWindow& window)
{
	sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));;
	int BoundX = mouse.x;
	int BoundY = mouse.y;
	std::cout << mouse.x << " / " << mouse.y << std::endl;
	if(BoundX >= 0 && BoundX <= 32 && BoundY >= 0 && BoundY <= 32)
	brushType = TILE_TREE;
	if(BoundX > 32 && BoundX <= 64 && BoundY >= 0 && BoundY <= 32)
	brushType = TILE_ROCK;
	if(BoundX >= 0 && BoundX <= 32 && BoundY >= 32 && BoundY <= 64)
	save();
	if(BoundX >= 32 && BoundX <= 64 && BoundY >= 32 && BoundY <= 64)
	;//LOAD
}

void Editor::save()
{
	std::string path = "res/map/map";
	std::cout << "Entrer le nom de la map\nmap";
	std::string slot;
	
	//Pas ouf je préfererais utiliser directement la fenetre plutôt que le terminal mais je suis pas trop sûr de comment procéder
	//Et aussi, attention à pas dépasser un nombre max je suppose
	std::cin >> slot;
	path.append(slot);
	
	path.append(".level");
	
	std::ofstream file(path);
	
	 if(file.is_open())
    {
		std::list<Actor*>::iterator actor = mapManager.getActorList().begin();
		while(actor != mapManager.getActorList().end())
		{
			file << dynamic_cast<Obstacle*>((*actor))->getType() << std::endl;
			file << (*actor)->getPosition().x << " " << (*actor)->getPosition().y << std::endl;
			actor++;
		}
	}
}
