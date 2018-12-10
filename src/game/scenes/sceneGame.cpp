//
// Created by fab on 14/11/18.
//

#include <iostream>
#include "../gameManager.h"
#include "sceneGame.h"
#include "../../util/Constants.h"

SceneGame::SceneGame(const char* mapPath, const char* player1ImgPath, const char* player2ImgPath)
: mapManager(mapPath)
{
    p1 = new Player(player1ImgPath, 1, true);
   // p2 = new Player(player2ImgPath, 1, false);

    playerPlaying = p1;

    p1->setPosition(mapManager.getFreePosition());
    mapManager.addActor(p1);

   // p2->setPosition(mapManager.getFreePosition());
   // mapManager.addActor(p2);

    mapManager.setDrawLines(true);

    isRightMouseButtonPressed = false;


    isPlayer1Turn = true;
}

void SceneGame::update()
{
    sf::RenderWindow& window = GameManager::Instance->getWindow();

    //check for closing window
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && playerPlaying->getIsAiming())
            {
                mapManager.collisionCheck(*playerPlaying);

                playerPlaying->setIsAiming(false);
            }
            else if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
            {
                playerPlaying->toggleAiming();
                playerPlaying->updateAimingLine(sf::Mouse::getPosition(window));
            }
        }
        else if(event.type == sf::Event::MouseMoved)
        {
            playerPlaying->updateAimingLine(sf::Mouse::getPosition(window));
        }
        else if (event.type == sf::Event::Closed)
            window.close();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();

    //draw stuff on the screen
    window.clear(GameManager::Instance->getClearColor());

    window.draw(mapManager);

    window.display();


}

SceneGame::~SceneGame() = default;
