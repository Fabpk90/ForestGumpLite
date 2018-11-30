//
// Created by fab on 14/11/18.
//

#include <iostream>
#include "../gameManager.h"
#include "sceneGame.h"
#include "../../util/constants.h"

SceneGame::SceneGame(const char* mapPath, const char* player1ImgPath, const char* player2ImgPath)
: mapManager(mapPath)
{
    p1 = new Player(player1ImgPath, 10, true);
    p2 = new Player(player2ImgPath, 10, false);

    p1->setPosition(mapManager.getFreePosition());
    mapManager.addActor(p1);

    p2->setPosition(mapManager.getFreePosition());
    mapManager.addActor(p2);

    mapManager.setDrawLines(true);

    isRightMouseButtonPressed = false;
}

void SceneGame::update()
{
    sf::RenderWindow& window = GameManager::Instance->getWindow();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();




    //draw stuff on the screen
    window.clear(GameManager::Instance->getClearColor());

    window.draw(mapManager);

    window.display();

    //check for closing window
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                sf::Vector2f size(32, 32);
                sf::Vector2f mousePos(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

                sf::FloatRect rect(mousePos, size);

                mapManager.collisionCheck(rect);

                if(isPlayer1Turn)
                {
                    p1->setIsAiming(false);
                }
                else
                {
                    p2->setIsAiming(false);
                }
            }
            else if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
            {
                if(isPlayer1Turn)
                {
                    p1->toggleAiming();
                    p1->updateAimingLine(sf::Mouse::getPosition(window));
                }
                else
                {
                    p2->toggleAiming();
                    p2->updateAimingLine(sf::Mouse::getPosition(window));
                }
            }
        }
        else if(event.type == sf::Event::MouseMoved)
        {
            if(isPlayer1Turn)
            {
                p1->updateAimingLine(sf::Mouse::getPosition(window));
            }
            else
            {
                p2->updateAimingLine(sf::Mouse::getPosition(window));
            }
        }
        else if (event.type == sf::Event::Closed)
            window.close();
    }
}

SceneGame::~SceneGame() = default;
