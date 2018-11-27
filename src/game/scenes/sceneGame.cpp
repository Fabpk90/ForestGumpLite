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

    clearColor.r = 0;
    clearColor.g = 255;
    clearColor.b = 128;

    loadLines();

}

void SceneGame::update()
{
    sf::RenderWindow& window = GameManager::Instance->getWindow();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();

    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        sf::Vector2f size(32, 32);
        sf::Vector2f mousePos(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

        sf::FloatRect rect(mousePos, size);

       mapManager.collisionCheck(rect);
    }

    //draw stuff on the screen
    window.clear(clearColor);

    window.draw(mapManager);
    window.draw(lineVertexPoints);

    window.display();

    //check for closing window
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

SceneGame::~SceneGame()
{

}


void SceneGame::loadLines()
{
    sf::RenderWindow& window = GameManager::Instance->getWindow();

    lineVertexPoints.setPrimitiveType(sf::PrimitiveType::Lines);

    sf::Vertex vertex;

    float sizeY = window.getSize().y / PIXEL_SIZE;
    float sizeX = window.getSize().x / PIXEL_SIZE;

    for (int i = 0; i < sizeY; ++i)
    {
        //first point of the line
        vertex.position = sf::Vector2f(0, i * PIXEL_SIZE);
        lineVertexPoints.append(vertex);

        //second point
        vertex.position = sf::Vector2f(window.getSize().x, i * PIXEL_SIZE);
        lineVertexPoints.append(vertex);

    }

    for (int i = 0; i < sizeX; ++i)
    {
        //first point of the line
        vertex.position = sf::Vector2f(i * PIXEL_SIZE, 0);
        lineVertexPoints.append(vertex);

        //second point
        vertex.position = sf::Vector2f(i * PIXEL_SIZE, window.getSize().y);
        lineVertexPoints.append(vertex);

    }

}
