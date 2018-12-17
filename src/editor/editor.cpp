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
        if (event.type == sf::Event::Closed)
            window.close();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))							//I have a goodish reason to use arrows to select what kind of stuff I want to place
			brushType = 0;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))							//But since It's the second time I have to do all that tonight I'm just saying screw that (I deleted the wrong branch and lost all progress, i'm a dumbass I know, git tryied t stop me but I didn't realize that until it was too late
			brushType = 1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))							//I'm fucking tired, youtube is down and we're going to have a power outage soon that will last way too long as in 5h+ long
			brushType = 2;
		if (event.type == sf::Event::MouseButtonReleased)							//But fret not, despite the small size of this code most of what still need to be done is either written on one of my whiteboards or stored in my unfauletering memory
			paint(window);															//wait nevermind, goole itself is down ? Fuck that gay ass shit I NEED TO CHECK HOW UNFAULTERING IS PROPERLY WRITTEN DAMNIT !
    }																				//Btw, i'll spend most of my monday working on my php project since i have to go get rapped tomorrow and I'm still not done with that
																					//I just wanted to relax before going to bed but youtube is down T.T
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();																//Well, that leaves me some time to talk about why i'm using arrows
}
																					//READ THAT DUDE: So I wanted to stretch a bit the window (by about 2*Pixel_Size) to get myself some room to create a kind of palette where you could click
Editor::~Editor()																	//on the obstacle you wanna use (the icon would have a red square around it to really make sure you know what you're using). In order to get the place I needed
{																					//I had to dable a bit (and by that i mean 2 and a half hour) with the loadlines. (I'm glossing over all the stupide stuff I tried) But in the end no matter what
																					//I did the amount of squares wouldn't go up ! I can decrease it easily but each time I tried to increase their amount I failed !
}																					//My first idea was to use a setSize in the editor builder to increase the x-axis space and then through the use of boolean and other stuff i would
																					//change sizeX = window.getSize().x / PIXEL_SIZE; into something like sizeX = (window.getSize().x - offset) / PIXEL_SIZE; which in theory would
Editor::Editor()																	//the same amount of lines as pre-streching, it turns out however that the fricking squares juste increase in width no matter what !
{																					//I tried to rebuild the mapmanager after making my setsize but to no avails, pretty much like everything else I've tried.
    mapManager.setDrawLines(true);													//I did succeed to limit the length of the horizontal lines (which was easy but then again, so should be the grid width thingy)
																					//Welp, my incoherente rent is now over, this was way to long to write it as a commentary but it's (literraly) too late.
    brushType = 0;																	//Oh and before I go, I couldn't push earlier 'cause I got 403 when I tried to push (on my branch)
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
