//
// Created by fab on 07/11/18.
//

#include "gameManager.h"

GameManager* GameManager::Instance = nullptr;

GameManager::GameManager(sf::Window* window)
{
    if(GameManager::Instance == nullptr)
    {
        GameManager::Instance = this;
        this->window = window;
    }
}

void GameManager::setScene(Scene *scene, bool isToBeDeleted)
{
    if(isToBeDeleted)
        delete scene;

    this->scene = scene;
}

void GameManager::renderScene()
{
    scene->update();
}

GameManager::~GameManager()
{
    delete scene;
}
