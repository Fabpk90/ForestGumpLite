//
// Created by fab on 14/11/18.
//

#include <iostream>
#include "../gameManager.h"
#include "sceneGame.h"

SceneGame::SceneGame(const char* mapPath, const char* player1ImgPath, const char* player2ImgPath)
: mapManager(mapPath)
{
    p1 = new Player(player1ImgPath, 10);
    p2 = new Player(player2ImgPath, 10);

    p1->setPosition(mapManager.getFreePosition());
    mapManager.addActor(p1);

    p2->setPosition(mapManager.getFreePosition());
    mapManager.addActor(p2);
}

void SceneGame::update()
{
    sf::RenderWindow& window = GameManager::Instance->getWindow();

    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();

    window.clear();

    window.draw(mapManager);

    window.display();
}
