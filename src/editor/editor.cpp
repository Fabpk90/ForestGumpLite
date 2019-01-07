//
// Created by fab on 28/11/18.
//

#include "editor.h"
#include "../game/gameManager.h"
#include "../util/Constants.h"
#include "../game/actors/obstacle.h"
#include "../game/scenes/sceneMainMenu.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>



void Editor::update()
{
    sf::RenderWindow& window = GameManager::Instance->getWindow();
		

    window.clear(GameManager::Instance->getClearColor());
    window.draw(mapManager);

    window.display();
		
		//Draw all the obstacles of the palette (catalog)
		for(auto actor : obstaclesP)
		{
			winPalette->draw(actor->getSprite());
		}
		sf::Event eventPal;
    
		
		winPalette->display();
		winPalette->clear(clearColor);
		
		//Event handling of the palette
		while (winPalette->pollEvent(eventPal))
		{

			if (eventPal.type == sf::Event::MouseButtonReleased)							
					brushSelect(*winPalette);													
		}																				
																				
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			winPalette->close();
	
		
		
    sf::Event event;
    //Event handling of the map
    while (window.pollEvent(event))
    {
		if (event.type == sf::Event::MouseButtonReleased)							
			paint(window);	//Place or remove an obstacle	
															
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
	//Activate line for mapping  conveniance																				
    mapManager.setDrawLines(true);				
    
    //Open the palette window
	winPalette = new sf::RenderWindow(sf::VideoMode(160, 128), "Palette");
	
	//Load the obstacles from the catalog onto the palette
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
	
	//Setup the map view
    view.setCenter(0, 0);
    view.setSize(sf::Vector2f(GameManager::Instance->getWindow().getSize()));
    GameManager::Instance->getWindow().setView(view);
}

//Draw an obstacle on the map
void Editor::paint(sf::RenderWindow& window)
{

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
	
	//Create an invisible rectangle the size of the currently selected obstacle
	sf::FloatRect paternRect(sf::Vector2f(BoundX, BoundY),sf::Vector2f(32,32));
	if(brushType == TILE_ROCK_BIG || brushType == TILE_TREE_BIG)
	{
		paternRect.width += 32;
		paternRect.height += 32;
	}
		
	bool isFound = false;
	
	//Goes through the map's obstacle list, remove all obstacles colliding with the paternRect
	//If no colliding obstacle is found, add an obstacle to the list
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

//Select obstacles and Save/Load/ChangeH health
void Editor::brushSelect(sf::RenderWindow& window)
{
	sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));;
	int BoundX = mouse.x;
	int BoundY = mouse.y;
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
	{load();}
	else if(BoundX >= 64 && BoundX <= 96 && BoundY >= 96 && BoundY <= 128)
	{setHealth();}
	else if(BoundX >= 0 && BoundX <= 32 && BoundY >= 96 && BoundY <= 128)
	{quit();}
}

void Editor::setHealth()
{
	//Get health from the console
	std::cout << "Combien de vie les prochains obstacles auront ?\n";
	std::string buf;
	std::getline(std::cin,buf);
	
	//Take care of the scenario in wich the user enters invalid amounts of health
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
	
	std::cout << "Vie mise à Jour\n";
}

void Editor::save()
{
	//Build the file's name
	std::string path = "res/map/map";
	std::cout << "Entrer le nom de la map\n";
	std::string slot;
	
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
			
			//Normalize the Coordinates
			file << (*actor)->getPosition().x / PIXEL_SIZE << " " << (*actor)->getPosition().y / PIXEL_SIZE << " " << (*actor)->getHealth() << std::endl;
			actor++;
		}
	}
	
	std::cout << "Map sauvegardee\n";
	file.close();
}

void Editor::load()
{
	//Build the file's name
	std::string path = "res/map/map";
	std::cout << "Entrer le nom de la map à charger\n";
	std::string slot;
	std::getline(std::cin,slot);
	path.append(slot);
	path.append(".level");
	
	//Create all the obstacles it reads and send an error if the file is not formated properly
	std::ifstream file(path);
	
	 if(file.is_open())
    {
		mapManager.getActorList().clear();
		int tileValue, Health, X, Y;
		
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
					mapManager.addActor(new Obstacle("res/texture/tree.png", Health, X*PIXEL_SIZE, Y*PIXEL_SIZE, TILE_TREE));
					break;
					
				case TILE_TREE_BIG:
					mapManager.addActor(new Obstacle("res/texture/BTree.png", Health, X*PIXEL_SIZE, Y*PIXEL_SIZE, TILE_TREE_BIG));
					break;
					
				case TILE_ROCK:
					mapManager.addActor(new Obstacle("res/texture/rock.png", Health, X*PIXEL_SIZE, Y*PIXEL_SIZE, TILE_ROCK));
					break;
					
				case TILE_ROCK_BIG:
					mapManager.addActor(new Obstacle("res/texture/BRock.png", Health, X*PIXEL_SIZE, Y*PIXEL_SIZE, TILE_ROCK_BIG));
					break;
					
				default:
					std::cerr << "Valeur d'obstacle non reconnu";
					exit(-1);
			}
		}
		
		std::cout << "Map chargee !\n";
	}
	else
	{
		std::cout << "Impossible d'ouvrire le fichier\n";
	}
	
	file.close();
}

void Editor::quit()
{
	winPalette->close();
	mapManager.getActorList().clear();
	GameManager::Instance->setScene(new SceneMainMenu());
}
