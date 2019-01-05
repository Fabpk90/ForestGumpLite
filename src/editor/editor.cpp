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
    
	winPalette = new sf::RenderWindow(sf::VideoMode(160, 128), "Palette");

    std::ifstream file("res/texture/catalog");
    int X, Y, tileValue;
    std::string path;
    
    if(file.is_open())
    {
		while(file >> path)
		{
			file >> X;
			file >> Y;
			file >> tileValue;
			
			obstaclesP.push_back(new Obstacle(path.c_str(), 1, X, Y, tileValue));
		}
		
	}
    file.close();
    
    
    winPalette->setKeyRepeatEnabled(false);													
    clearColor.r = 0;
    clearColor.g = 0;
    clearColor.b = 0;										
    brushType = 0;
	Health = 1;
	
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
	
	sf::FloatRect paternRect(sf::Vector2f(BoundX, BoundY),sf::Vector2f(32,32));
	if(brushType == TILE_ROCK_BIG || brushType == TILE_TREE_BIG)
	{
		paternRect.width += 32;
		paternRect.height += 32;
	}
		
	bool isFound = false;
	
	std::cout << BoundX << " " << mouse.x << " / " << BoundY << " " << mouse.y << std::endl;
	std::list<Actor*>::iterator actor = mapManager.getActorList().begin();
	while(actor != mapManager.getActorList().end())
	{
		
		if ((*actor)->getGlobalBounds().intersects(paternRect))
		{
			mapManager.getActorList().erase(actor++);
			isFound = true;
			std::cout << "BOOM\n";
		}
		else if(actor !=  mapManager.getActorList().end())
			++actor;
	}
	if(!isFound)
	{
		switch(brushType)
		{
			case TILE_TREE:
				mapManager.addActor(new Obstacle("res/texture/tree.png", Health, BoundX, BoundY, TILE_TREE));
			break;

			case TILE_ROCK:
				mapManager.addActor(new Obstacle("res/texture/rock.png", Health, BoundX, BoundY, TILE_ROCK));
			break;
			
			case TILE_TREE_BIG:
				mapManager.addActor(new Obstacle("res/texture/BTree.png", Health, BoundX, BoundY, TILE_TREE_BIG));
			break;

			case TILE_ROCK_BIG:
				mapManager.addActor(new Obstacle("res/texture/BRock.png", Health, BoundX, BoundY, TILE_ROCK_BIG));
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
	{brushType = TILE_TREE;}
	else if(BoundX >= 0 && BoundX <= 32 && BoundY >= 32 && BoundY <= 64)
	{brushType = TILE_ROCK;}
	else if(BoundX >= 32 && BoundX <= 96 && BoundY >= 0 && BoundY <= 64)
	{brushType = TILE_TREE_BIG;}
	else if(BoundX >= 96 && BoundX <= 160 && BoundY >= 0 && BoundY <= 64)
	{brushType = TILE_ROCK_BIG;}
	else if(BoundX >= 96 && BoundX <= 128 && BoundY >= 96 && BoundY <= 128)
	{save();}
	else if(BoundX >= 128 && BoundX <= 160 && BoundY >= 96 && BoundY <= 128)
	{;}//LOAD//////////////////////////////////////////////////////////////////
	else if(BoundX >= 64 && BoundX <= 96 && BoundY >= 96 && BoundY <= 128)
	{setHealth();}
}

void Editor::setHealth()
{
	std::cout << "Combien de vie les prochains obstacles auront ?\n";
	std::string buf;
	std::getline(std::cin,buf);
	
	try {
		Health = std::stoi(buf);
	}
	catch (std::invalid_argument)
	{
		std::cout << "argument invalide, vie inchangée\n";
	}
	catch (std::out_of_range)
	{
		std::cout << "nombre trop grand, vie inchangée\n";
	}
}

void Editor::save()
{
	std::string path = "res/map/map";
	std::cout << "Entrer le nom de la map\n";
	std::string slot;
	
	//Pas ouf je préfererais utiliser directement la fenetre plutôt que le terminal mais je suis pas trop sûr de comment procéder
	//Et aussi, attention à pas dépasser un nombre max je suppose
	std::getline(std::cin,slot);
	path.append(slot);
	
	path.append(".level");
	
	std::ofstream file(path);
	
	 if(file.is_open())
    {
		std::list<Actor*>::iterator actor = mapManager.getActorList().begin();
		while(actor != mapManager.getActorList().end())
		{
			file << dynamic_cast<Obstacle*>((*actor))->getType() << std::endl;
			file << (*actor)->getPosition().x << " " << (*actor)->getPosition().y << " " << (*actor)->getHealth() << std::endl;
			actor++;
		}
	}
	
	file.close();
}
