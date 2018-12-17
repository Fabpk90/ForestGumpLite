//
// Created by fab on 07/11/18.
//
#include "../util/Constants.h"
#include <iostream>
#include "gameManager.h"

GameManager* GameManager::Instance = nullptr;

GameManager::GameManager()
{
    if(GameManager::Instance == nullptr)
    {
        GameManager::Instance = this;
        window = new sf::RenderWindow(sf::VideoMode(SCREEN_SIZE_WIDTH, SCREEN_SIZE_HEIGHT), "ForestGumpLite");
        window->setKeyRepeatEnabled(false);

        clearColor.r = 0;
        clearColor.g = 255;
        clearColor.b = 128;

        scene = nullptr;
    }
}

void GameManager::setScene(Scene *scene, bool isOldToBeDeleted)
{
    if(isOldToBeDeleted)
        delete scene;

    this->scene = scene;
}

void GameManager::renderScene()
{
    scene->update();
}

void GameManager::editorMode()
{
    editor->update();
}

GameManager::~GameManager()
{
    delete scene;
    delete window;
}

void GameManager::setWinner(bool isWinnerPlayer1)
{
    if(isWinnerPlayer1)
        std::cout << "Player 1 has won!  Shame on you player 2!";
    else
        std::cout << "Player 2 has won!  Shame on you player 1!";
}
